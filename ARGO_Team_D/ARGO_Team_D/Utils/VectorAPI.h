#ifndef VECTORAPI_H
#define VECTORAPI_H

//INCLUDES
#include <math.h>

class VectorAPI
{
public:
	//CONSTRUCTORS
	VectorAPI();
	VectorAPI(float xValue, float yValue);
	VectorAPI(const VectorAPI & v);
	~VectorAPI();

	// METHODS
	void Set(float xValue, float yValue);
	void Set(VectorAPI & v);
	void Set(VectorAPI * v);

	float Length() const;
	float LengthSquared() const;
	float Distance(const VectorAPI & v) const;
	float DistanceSquared(const VectorAPI & v) const;
	float Dot(const VectorAPI & v) const;
	float Cross(const VectorAPI & v) const;
	void Truncate(float upperBound);

	float Normal();
	VectorAPI & Normalize();

	//ASSINGMENT AND EQUALITY OPERATIONS
	inline VectorAPI & operator = (const VectorAPI & v) { x = v.x; y = v.y; return *this; }
	inline VectorAPI & operator = (const float & f) { x = f; y = f; return *this; }
	inline VectorAPI & operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const VectorAPI & v) const { return (x == v.x) && (y == v.y); }
	inline bool operator != (const VectorAPI & v) const { return (x != v.x) || (y != v.y); }

	//VECTOR2 TO VECTOR2 OPERATIONS
	inline const VectorAPI operator + (const VectorAPI & v) const { return VectorAPI(x + v.x, y + v.y); }
	inline const VectorAPI operator - (const VectorAPI & v) const { return VectorAPI(x - v.x, y - v.y); }
	inline const VectorAPI operator * (const VectorAPI & v) const { return VectorAPI(x * v.x, y * v.y); }
	inline const VectorAPI operator / (const VectorAPI & v) const { return VectorAPI(x / v.x, y / v.y); }

	//VECTOR2 TO THIS OPERATIONS
	inline VectorAPI & operator += (const VectorAPI & v) { x += v.x; y += v.y; return *this; }
	inline VectorAPI & operator -= (const VectorAPI & v) { x -= v.x; y -= v.y; return *this; }
	inline VectorAPI & operator *= (const VectorAPI & v) { x *= v.x; y *= v.y; return *this; }
	inline VectorAPI & operator /= (const VectorAPI & v) { x /= v.x; y /= v.y; return *this; }

	//SCALER TO VECTOR2 OPERATIONS
	inline const VectorAPI operator + (float v) const { return VectorAPI(x + v, y + v); }
	inline const VectorAPI operator - (float v) const { return VectorAPI(x - v, y - v); }
	inline const VectorAPI operator * (float v) const { return VectorAPI(x * v, y * v); }
	inline const VectorAPI operator / (float v) const { return VectorAPI(x / v, y / v); }

	//SCALER TO THIS OPERATIONS
	inline VectorAPI & operator += (float v) { x += v; y += v; return *this; }
	inline VectorAPI & operator -= (float v) { x -= v; y -= v; return *this; }
	inline VectorAPI & operator *= (float v) { x *= v; y *= v; return *this; }
	inline VectorAPI & operator /= (float v) { x /= v; y /= v; return *this; }

	//COMPARISON OPERATION
	bool operator<(VectorAPI const& rhs) { return (x < rhs.x) || ((x == rhs.x) && (y < rhs.y)); }

	float x = 0.0;
	float y = 0.0;
};
#endif // !VECTORAPI_H

