
#include "general.h"
#include "vMath.h"
//using namespace std;
#define EPSILON 0.000001
/*
template<typename T>
bool solveQuadratic(const T &a, const T &b, const T &c, T &x0, T &x1)
{
	T discr = b * b - 4 * a * c;
	if (discr < -EPSILON) return false;
	else if (discr < EPSILON) x0 = x1 = -0.5 * b / a;
	else {
		T q = (b>0) ?
		    -0.5 * (b + sqrt(discr)) :
		    -0.5 * (b - sqrt(discr));
		    x0 = q/a;
		    x1 = c/q;
	
	}
	if(x0 > x1) std::swap(x0, x1);
	return true;
}
*/


/*

int main() 
{
v3 a = {1,2,3};
v3 b = {5,6,7};
v3 c = {6,7,8};

tri t = {a,b,c};
orb o = {a,2,2*2};
cam c1 = {b,c};



}
*/
