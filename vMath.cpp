#include <cmath>
#include <stdio.h>
#include "vMath.h"






//get transformation matrix for translation by vector t
m4x4 mTranslate(v3 t)
{
 m4x4 m = {{
 {1,0,0,t.x},
 {0,1,0,t.y},
 {0,0,1,t.z},
 {0,0,0,1}
 }};
 return m;
}


//get matrix for rotation around x axis by phi radians
m4x4 mRotateX (double phi)
{
	m4x4 m = 
	{
		{
			{1,0,0,0},
			{0,cos(phi),-sin(phi),0},
			{0,sin(phi),cos(phi),0},
			{0,0,0,1}
		}
	};
	return m;
}

//get matrix for rotation around y axis by phi radians
m4x4 mRotateY (double phi)
{
	m4x4 m = 
	{
		{
			{cos(phi),0,sin(phi),0},
			{0,1,0,0},
			{-sin(phi),0,cos(phi),0},
			{0,0,0,1}
		}
	};
	return m;
}

//get matrix for rotation around z axis by phi radians
m4x4 mRotateZ (double phi)
{
	m4x4 m = 
	{
		{
			{cos(phi),-sin(phi),0,0},
			{sin(phi),cos(phi),0,0},
			{0,0,1,0},
			{0,0,0,1}
		}
	};
	return m;
}
/*
  int main() 
  {
	v3 a = {3,0,0};
	v3 b = {0,3,0};
	b.norm();
	v3 c = -b;
	double angle = a.angle(b);
	printf("[%5.2f,%5.2f,%5.2f]\n",a.x,a.y,a.z);
	printf("[%5.2f,%5.2f,%5.2f]\n",b.x,b.y,b.z);
	printf("[%5.2f,%5.2f,%5.2f]\n",c.x,c.y,c.z);
  	printf("angle between a and b : %5.2f \n",angle);
  }
*/
