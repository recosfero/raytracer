#ifndef VMATH
#define VMATH

struct v4 {

  double x,y,z,a;

  
  v4 operator+=(v4 &v);
  v4 operator-=(v4 &v);
  v4 operator+(v4 &v);
  v4 operator-(v4 &v);
  v4 operator-();


  double length();

  v4 norm();

  v4 cross(v4 &v);

  double scalar(v4 &v);

  double operator*(v4 &v);

  double angle(v4 &v);
  };

struct v3 {

  double x,y,z;

  
  v3 operator+=(v3 &v);
  v3 operator-=(v3 &v);
  v3 operator+(v3 &v);
  v3 operator-(const v3 &v) const;
  v3 operator-();


  double length();

  v3 norm();

  v3 cross(v3 &v) const;

  double scalar(v3 &v) const;

  double operator*(v3 &v) const;

  double angle(v3 &v);
  };

#endif
