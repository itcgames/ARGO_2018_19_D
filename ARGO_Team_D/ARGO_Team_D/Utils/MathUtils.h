#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "VectorAPI.h"

namespace mu {
	#define PI 3.14159265
	float degToRadians(const float deg);
	float radToDegrees(const float rad);
	float lerp(const float start, const float end, const float percent);
	VectorAPI lerp(const VectorAPI & start, const VectorAPI & end, float percent);
}

#endif // !MATHUTILS_H
