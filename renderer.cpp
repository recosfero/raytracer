#include <cmath>
#include <cstring>
#include "vMath.h"

int main() 
{
	unsigned int width = 640, height=480, i, j;
	double Px,Py;
	unsigned char *buffer = new unsigned char [width * height * 3], *pix = buffer; 
	memset(buffer, 0x0, sizeof(unsigned char) * width * height);

	double focal = 60.0;
	double angle = tan(focal * 0.5 * M_PI / 180);
	double aspectR = float(width / height);

	// transform coordinates to camera space

	for (i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			//map from raster to screen space
			Px = ((2 * (j + 0.5d) / width) -1) * aspectR * angle;
			Py = (1 - (i + +0.5d) / width) *  angle;

			//create ray direction, looking down z-axis
			v3 rayDir;
			v3 pixPoint= {Px,Py,-1};
			v3 camOrigin = {0.0,0.0,0.0};
			
			//TODO: transform from camera to world space
			
			rayDir = pixPoint - camOrigin;
			rayDir.norm();

		}
	}

	/*
 // save to PPM std::ofstream ofs; ofs.open("./untitled.ppm"); ofs << "P6\n" << width << " " << height << "\n255\n"; ofs.write((char*)buffer, sizeof(unsigned char) * width * height * 3); ofs.close(); delete [] buffer;
	*/

}

