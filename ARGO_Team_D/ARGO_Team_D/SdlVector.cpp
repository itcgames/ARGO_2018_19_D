#include "SdlVector.h"

SdlVector::SdlVector() : x(0), y(0) {}

SdlVector::SdlVector(float xIn, float yIn) : x(xIn), y(yIn) {}

SdlVector::~SdlVector() {}

//SdlVector SdlVector::operator+(const SdlVector & vec)
//{
//	return SdlVector(x + v.x, y + v.y);
//}
//
//SdlVector SdlVector::operator-(const SdlVector & vec)
//{
//	return SdlVector(x - v.x, y - v.y);
//}
//
//SdlVector SdlVector::operator*(const SdlVector & val)
//{
//	return SdlVector(x + v.x, y + v.y);
//}
//
//SdlVector SdlVector::operator/(const float & val)
//{
//	return SdlVector(x + v.x, y + v.y);
//}