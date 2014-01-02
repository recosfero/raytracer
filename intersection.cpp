#include "vMath.h"

#define EPSILON 0.000001
 
 //Möller Trumbore
int triangle_intersection( const v3   A,  // Triangle vertices
                           const v3   B,
                           const v3   C,
                           const v3    O,  //Ray origin
                           const v3    D,  //Ray direction
			   float* out )
{
  v3 e1, e2;  //Edge1, Edge2
  v3 P, Q, T;
  float det, inv_det, u, v;
  float t;
 
  //Find vectors for two edges sharing a
  e1 = B - A;
  e2 = C - A;
  //Begin calculating determinant - also used to calculate u parameter
  P = D.cross(e2);
  //if determinant is near zero, ray lies in plane of triangle
  det = e1.scalar(P);
  //NOT CULLING
  if(det > -EPSILON && det < EPSILON) return 0;
  inv_det = 1.f / det;
 
  //calculate distance from a to ray origin
  T = O - A;
 
  //Calculate u parameter and test bound
  u = T.scalar(P) * inv_det;
  //The intersection lies outside of the triangle
  if(u < 0.f || u > 1.f) return 0;
 
  //Prepare to test v parameter
  Q = T.cross(e1);
 
  //Calculate V parameter and test bound
  v = D.scalar(Q) * inv_det;
  //The intersection lies outside of the triangle
  if(v < 0.f || u + v  > 1.f) return 0;
 
  t = e2.scalar(Q) * inv_det;
 
  if(t > EPSILON) { //ray intersection
    *out = t;
    return 1;
  }
 
  // No hit, no win
  return 0;
}

int main() {

}
