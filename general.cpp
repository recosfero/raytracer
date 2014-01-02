#include <string>
#include "vMath.h"
#include <list>

//using namespace std;

struct ray
{
	v4 ori, dir;
	double tmin,tmax;
}

struct tri
{
v4 a,b,c;

};

struct orb
{
v4 pos;
double r;


bool intersect(ray r)
{
	double a,b,c,t0,t1;
	v4 L = ray.ori - pos;
	//a = 1 if vectors are normalised
	a = ray.dir.scalar(ray.dir);
	b = 2 * ray.dir.scalar(L);
	c = L.scalar(L) - r * r;
	if(!solveQuadratic(a,b,c,t0,t1) return false;

	if (t0 > ray.tmax) return false;
	else ray.tmax = t0;
	return true;
}
};


struct cam
{
v4 from, to, up;
double fov;

};

struct scene {
  tri[] triList;
  orb[] orbList;
};

struct img {
  scene s;
  cam c;
  int width, height;
  string outfile;

  void getRays()
  {
  }

};

template<typename T>
bool solveQuadratic(const T &a, const T &b, const T &c, T &x0, T &x1)
{
	T discr = b * b - 4 * a * c;
	if (discr <0) return false;
	else if (discr == 0) x0 = x2 = -0.5 * b / a;
	else {
		T q = (b>0) ?
		    -0.5 * (b + sqrt(discr)) :
		    -0.5 * (b - sqrt(discr));
		    x0 = q/a;
		    x1 = c/q;
	
	}
	if(x0 > x1) std::swqp(x0, x1);
	return true;
}

bool intersectTriangle(ray r, tri t)
{

}

struct tfStack {

std::list<m4x4> matrices;
m4x4 transformAll;

	tfStack()
	{
		
		transformAll.setIdentity();
	}

	void push(m4x4 m)
	{
		matrices.push_front(m);	
		transformAll = transformAll.mmult(m);
	}

	m4x4 pop()
	{
		m4x4 m =  matrices.pop_front();
		if(!matrices.empty()) 
		{
			multAll();
		}
		else {
			transformAll.setIdentity();
		}
		return m; 
	}

	multAll(){
		for(std::list<m4x4>::reverse_iterator it =matrices.rbegin(); it != matrices.rend(); ++it)
		{
			transformAll = transformAll.mmult(*it);
		}
	}

};


int main() 
{
v4 a = {1,2,3,1};
v4 b = {5,6,7,1};
v4 c = {6,7,8,1};

tri t = {a,b,c};
orb o = {a,b};
cam c1 = {b,c};

}
