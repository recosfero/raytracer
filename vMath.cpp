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

struct v3
{
  double x,y,z;

  
  v3 operator+=(v3 &v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  
  v3 operator-=(v3 &v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  v3 operator+(v3 &v){
  	v3 s = {x+v.x,y+v.y,z+v.z};
	return(s);
  }

  v3 operator-(const v3 &v) const
  {
  	v3 s = {x-v.x,y-v.y,z-v.z};
	return(s);
  }
  
  v3 operator-(){
  	x = -x;
	y = -y;
	z = -z;
	return *this;
  }


  double length()
  {
	return(sqrt( x*x + y*y + z*z));
  }

  v3 norm()
  {
	double l = this->length();
	x /= l;
	y /= l;
	z /= l;
	return *this;
  }

  v3 cross(v3 &v) const
  {
  	v3 s = { y*v.z-z*v.y , x*v.z - z * v.x, x*v.y - y*v.x };
	return(s);
	
  }

  double scalar(v3 &v) const
  {
	return(x*v.x+y*v.y+z*v.z);
  }

  double operator*(v3 &v) const
  {
	return(x*v.x+y*v.y+z*v.z);

  }

  double angle(v3 &v){
  	this->norm();
	v.norm();
	return acos(this->scalar(v));
  }
};


struct m4x4{

	double m[4][4];

	void setIdentity()
	{
		m[0][0] = 1;
		m[0][1] = 0;
		m[0][2] = 0;
		m[0][3] = 0;
		m[1][0] = 0;
		m[1][1] = 1;
		m[1][2] = 0;
		m[1][3] = 0;
		m[2][0] = 0;
		m[2][1] = 0;
		m[2][2] = 1;
		m[2][3] = 0;
		m[3][0] = 0;
		m[3][1] = 0;
		m[3][2] = 0;
		m[3][3] = 1;


	}
	v3 v3Mult(const v3 v)
	{
		v3 res;
		res.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3];
		res.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3];
		res.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3];
		return res;
	}

	m4x4 mmult(m4x4 b)
	{
		int i,j,k;
		m4x4 c;
		for (i=0; i<4; i++)
		{
			for(j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				{
					c.m[i][j] += m[i][k] * b.m[k][j];
				}
			}
		}
		return c;
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
