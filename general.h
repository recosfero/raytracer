#include <string>
#include "vMath.h"
#include <list>
#include <fstream>

#define EPSILON 0.000001

struct ray
{
	v3 ori, dir;
	double tmin,tmax;
};


struct material {
	float color[];
	double alpha, reflect;
	
};

struct tri
{
v3 a,b,c;

};

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


struct orb
{
v3 pos;
double radius,radius2;
float color[3];

bool intersect(ray &r)
{
	double a,b,c,t0,t1;
	v3 L = r.ori - pos;
	//a = 1 if vectors are normalised
	a = r.dir.scalar(r.dir);
	b = 2 * r.dir.scalar(L);
	c = L.scalar(L) - radius2;
	if(!solveQuadratic(a,b,c,t0,t1)) return false;
	
	//if (t0 > r.tmax) return false;
	//else r.tmax = t0;
	return true;
}
};


struct cam
{
v3 from, to, up;
double fov;

};

struct scene {
  tri triList[];
  orb orbList[];
};

struct Image { 
	
	Image(const int &w, const int &h) : width(w), height(h) 
	{
		 imageData = new float [w * h * 3]; 
		// red = new float[w * h];
		// green= new float[w * h];
		// blue = new float[w * h];
	} 
	~Image() 
	{
		 delete [] imageData; 
	} 
	
	void setPixel(const float *pixelValues, const int &x, const int &y) 
	{ 
		imageData[(y * width + x) * 3] = pixelValues[0]; 
		imageData[(y * width + x) * 3 + 1] = pixelValues[1]; 
		imageData[(y * width + x) * 3 + 2] = pixelValues[2]; 


	} 
	
	void saveToPpm(const char *filename) 
	{ 
		std::ofstream ofs; 
		ofs.open(filename); 
		ofs << "P6\n" << width << " " << height << "\n255\n"; 
		float *pixel = imageData; 
		for (int j = 0; j < height; ++j) 
		{ 
			for (int i = 0; i < width; ++i) 
			{ 
				//int pos = (i * width + j);
				//unsigned char r = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[0], 1/2.2) * 255 + 0.5f))); 
				//unsigned char g = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[1], 1/2.2) * 255 + 0.5f))); 
				//unsigned char b = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[2], 1/2.2) * 255 + 0.5f))); 
				unsigned char r = (unsigned char)(std::max(0.f, std::min(255.f, pixel[0] * 255 + 0.5f))); 
				unsigned char g = (unsigned char)(std::max(0.f, std::min(255.f, pixel[1] * 255 + 0.5f))); 
				unsigned char b = (unsigned char)(std::max(0.f, std::min(255.f, pixel[2] * 255 + 0.5f))); 
				//unsigned char r = (unsigned char)(red[pos]); 
				//unsigned char g = (unsigned char)(green[pos]); 
				//unsigned char b = (unsigned char)(blue[pos]); 
				
				ofs << r << g << b; 
				
				//printf("Set %5.2f,%5.2f,%5.2f\n",pixel[0],pixel[1],pixel[2]);
				//printf("Set %5.2f,%5.2f,%5.2f\n\n",std::max(0.f, std::min(255.f, powf(pixel[0], 1/2.2) * 255 + 0.5f)),std::max(0.f, std::min(255.f, powf(pixel[1], 1/2.2) * 255 + 0.5f)),std::max(0.f, std::min(255.f, powf(pixel[2], 1/2.2) * 255 + 0.5f)));
				//printf("Set %5.2f,%5.2f,%5.2f\n\n",std::max(0.f, std::min(255.f, pixel[0] * 255 + 0.5f)),std::max(0.f, std::min(255.f, pixel[1] * 255 + 0.5f)),std::max(0.f, std::min(255.f, pixel[2] * 255 + 0.5f)));

				pixel += 3; 
			} 
		} 
		ofs.close();
	}
	
	void readPpm(const char *filename) 
	{ 
		return;
	} 
	
	float *imageData;
	int width, height; 
};

/**
 * Stack of transformation matrices
 * 
 * 
 */
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
		multAll();
	}

	m4x4 pop()
	{
		m4x4 m =  matrices.front();
		matrices.pop_front();
		multAll();
		return m; 
	}

	void multAll(){
		if(matrices.empty())
		{
			transformAll.setIdentity();
		}
		else
		{
			
			for(std::list<m4x4>::const_iterator it =matrices.begin(); it != matrices.end(); ++it)
			{
				if(it==matrices.begin())
				{
					transformAll = *it;
					
				} 
				else
				{
					transformAll = transformAll.mmult(*it);
			
					
				}
				
			}
		}
	}

};




