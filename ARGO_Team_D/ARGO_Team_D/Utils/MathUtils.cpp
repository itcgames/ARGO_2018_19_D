#include "MathUtils.h"

/// <summary>
/// Utility function to convert from degrees to radians
/// </summary>
/// <param name="deg">The degrees value as a floating point number</param>
/// <returns>The radians value as a floating point number</returns>
float mu::degToRadians(const float deg)
{
	return deg * (PI / 180.0f);
}

/// <summary>
/// Utility function to convert radians to degrees
/// </summary>
/// <param name="rad">The degrees in raidians</param>
/// <returns></returns>
float mu::radToDegrees(const float rad)
{
	return rad * (180.0f / PI);
}

float mu::lerp(const float start, const float end, const float percent)
{
	return (start + percent * (end - start));
}

VectorAPI mu::lerp(const VectorAPI & start, const VectorAPI & end, float percent)
{
	return start + ((end - start) * percent);
}
