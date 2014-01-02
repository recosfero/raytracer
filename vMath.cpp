#include <cmath>
#include <stdio.h>
#include "vMath.h"

struct v4 {

  double x,y,z,a;

  
  v4 operator+=(v4 &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  
  v4 operator-=(v4 &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  v4 operator+(v4 &v){
  	v4 s = {x+v.x,y+v.y,z+v.z,0};
	return(s);
  }

  v4 operator-(v4 &v){
  	v4 s = {x-v.x,y-v.y,z-v.z,0};
	return(s);
  }
  
  v4 operator-(){
  	x = -x;
	y = -y;
	z = -z;
	return *this;
  }


  double length()
  {
	return(sqrt( x*x + y*y + z*z));
  }

  v4 norm()
  {
	double l = this->length();
	x /= l;
	y /= l;
	z /= l;
	return *this;
  }

  v4 cross(v4 &v)
  {
  	v4 s = { y*v.z-z*v.y , x*v.z - z * v.x, x*v.y - y*v.x, 0 };
	return(s);
	
  }

  double scalar(v4 &v){
	return(x*v.x+y*v.y+z*v.z);
  }

  double operator*(v4 &v)
  {
	return this->scalar(v);

  }

  double angle(v4 &v){
  	this->norm();
	v.norm();
	return acos(this->scalar(v));
  }
  };




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

  int main() 
  {
	v4 a = {3,0,0,0};
	v4 b = {0,3,0,0};
	b.norm();
	v4 c = -b;
	double angle = a.angle(b);
	printf("[%5.2f,%5.2f,%5.2f,%5.2f]\n",a.x,a.y,a.z,a.a);
	printf("[%5.2f,%5.2f,%5.2f,%5.2f]\n",b.x,b.y,b.z,b.a);
	printf("[%5.2f,%5.2f,%5.2f,%5.2f]\n",c.x,c.y,c.z,c.a);
  	printf("angle between a and b : %5.2f \n",angle);
  }
