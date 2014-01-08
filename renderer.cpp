#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include "vMath.h"
#include "general.h"


tfStack getCamToWorldTransform(cam c)
{
	double angle;
	tfStack t;
	m4x4 translate = m4x4::mTranslate(-c.from);
//	t.transformAll.printMatrix();
//	translate.printMatrix();
	t.push(translate);
//	t.transformAll.printMatrix();
	
	v3 dir = c.to - c.from;
	dir.norm();
	
	//-z corresponds to scalar product with (0,0,-1), the default camera direction
	
	if(dir.x != 0 || dir.z !=0) {
		angle = acos(-dir.z);
		t.push(m4x4::mRotateY(-angle));
	//	m4x4::mRotateY(-angle).printMatrix();
	}
	if(dir.y != 0 || dir.z !=0) {
		angle = acos(-dir.z);
		t.push(m4x4::mRotateX(-angle));
	//	m4x4::mRotateX(-angle).printMatrix();
	}

	return t;
	
	
}

void traceRay(ray &r,float* col)
{
	//int tri_length = sizeof(s.triList) / sizeof(s.triList[0]);
	orb o = {{0,0,-9},2,4,{0.0f,0.0f,255.0f}};
	
	if(o.intersect(r))
	{
		//printf("ray hit something");
		//return o.color;
		col[0] = o.color[0];
		col[1] = o.color[1];
		col[2] = o.color[2];
	}
	else
	{
		col[0] = 0.0f;
		col[1] = 0.0f;
		col[2] = 0.0f;
	}
	
}

int main() 
{
	unsigned int width = 640, height=480, i, j;
	double Px,Py;
	Image img = Image(width,height);

	double focal = 120.0;
	double angle = tan(focal * 0.5 * M_PI / 180);
	double aspectR = double(width) / height;

	cam c = {
			{0,0,0},  //from
			{0,0,-1}, //to
			{0,1,0},  //up
			120		  //fov
		};

	tfStack tf = getCamToWorldTransform(c);
	//tf.transformAll.printMatrix();
	// transform coordinates to camera space
	float colBuffer[3];
	memset(colBuffer,0x0,3);
	
	
	//set custom scene
	

	for (j=0;j<height;j++)
	{
		for(i=0;i<width;i++)
		{
			//map from raster to screen space
			Px = ((2 * (i + 0.5d) / width) -1) * aspectR * angle;
			Py = (1 - 2 * (j + 0.5d) / height) *  angle;
			
			// remap from raster to screen space 
			//float xx = (2 * (i + 0.5) / width - 1) * angle * imageAspectRatio; 
			//float yy = (1 - 2 * (j + 0.5) / height) * angle; 

			//create ray direction, looking down z-axis
			v3 rayDir;
			v3 pixPoint= {Px,Py,-1};
			v3 camOrigin = c.from;
			
			//printf("%5.4f,%5.4f \n",pixPoint.x,pixPoint.y);
			
			//TODO: transform from camera to world space
			pixPoint = tf.transformAll.v3Mult(pixPoint);
			//printf("%5.4f,%5.4f \n\n",pixPoint.x,pixPoint.y);
			
			
			rayDir = pixPoint - camOrigin;
			rayDir.norm();
			//printf("%5.4f,%5.4f,%5.4f \n",rayDir.x,rayDir.y,rayDir.z);
			ray camRay = {camOrigin,rayDir};

			//trace the ray
			traceRay(camRay,colBuffer);

			//printf("%5.2f,%5.2f,%5.2f \n",col[0],col[1],col[2]);
			img.setPixel(colBuffer,i,j);
			
			//set the pixel
			
			
		}
	}

	img.saveToPpm("./test.ppm");

	
	
	
	return 0;


}

