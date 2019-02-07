#include "VectorAPI.h"

//Constructors
VectorAPI::VectorAPI(void) : x(0), y(0) { }
VectorAPI::VectorAPI(float xValue, float yValue) : x(xValue), y(yValue) { }
VectorAPI::VectorAPI(const VectorAPI & v) : x(v.x), y(v.y) { }
VectorAPI::~VectorAPI() {}

//METHODS
void VectorAPI::Set(float xValue, float yValue) {
	x = xValue; y = yValue; 
}

void VectorAPI::Set(VectorAPI & v)
{
	x = v.x;
	y = v.y;
}

void VectorAPI::Set(VectorAPI * v)
{
	x = v->x;
	y = v->y;
}

float VectorAPI::Length() const { 
	return sqrt(x * x + y * y); 
}

float VectorAPI::LengthSquared() const { 
	return x * x + y * y; 
}

float VectorAPI::Distance(const VectorAPI & v) const { 
	return sqrt(((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y)));
}

float VectorAPI::DistanceSquared(const VectorAPI & v) const {
	return ((x - v.x) * (x - v.x)) + ((y - v.y) * (y - v.y));
}

float VectorAPI::Dot(const VectorAPI & v) const { 
	return x * v.x + y * v.y;
}

float VectorAPI::Cross(const VectorAPI & v) const { 
	return x * v.y - y * v.x; 
}

void VectorAPI::Truncate(float upperBound)
{
	float sqrLen = LengthSquared();

	if (sqrLen > upperBound * upperBound)
	{
		float mult = upperBound / sqrt(sqrLen);
		x *= mult; y *= mult;
	}
}

float VectorAPI::Normal() {
	return sqrt(((x*x) + (y*y)));
}

VectorAPI & VectorAPI::Normalize()
{
	if (Length() != 0)
	{
		float length = Normal();
		x /= length; y /= length;
		return *this;
	}

	x = y = 0;
	return *this;	
}
