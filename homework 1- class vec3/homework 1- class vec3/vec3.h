#ifndef vec3_H
#define vec3_H

#include <iostream>
#include <math.h>
using namespace std;

template <class T>
class vec3
{
private:
	T x;
	T y;
	T z;
public:
	vec3() : x(0), y(0), z(0) {}
	vec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
	vec3(T* vec) : x(vec[0]), y(vec[1]), z(vec[2]) {}

	void operator+= (const vec3 v) const
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void operator-= (const vec3 v) const
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	void operator= (const vec3 v) const
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	bool operator== (const vec3 v) const
	{
		return v.x == x && v.y == y && v.z == z;
	}

	vec3 operator+ (const vec3 v) const
	{
		vec3 newvec;

		newvec.x = x + v.x;
		newvec.y = y + v.y;
		newvec.z = z + v.z;

		return newvec;
	}

	vec3 operator- (const vec3 v) const
	{
		vec3 newvec;

		newvec.x = x - v.x;
		newvec.y = y - v.y;
		newvec.z = z - v.z;

		return newvec;
	}

public:

	void normalize() 
	{
		x = x / sqrt(x*x + y * y + z * z);
		y = y / sqrt(x*x + y * y + z * z);
		z = z / sqrt(x*x + y * y + z * z);
	}

	void zero() 
	{
		x = 0;
		y = 0;
		z = 0;
	}

	bool is_zero() 
	{
		return x == 0 && y == 0 && z == 0;
	}

	vec3 distance_to(const vec3 v)
	{
		vec3 newvec;
		
		newvec.x = v.x - x;
		newvec.y = v.y - y;
		newvec.z = v.z - z;
		
		return newvec;
	}

};
#endif