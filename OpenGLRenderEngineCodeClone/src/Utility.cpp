
#include "Utility.h"
float Utility::colorDistort(float r)
{
	if (r >= 1.0f)
		r = 0;
	r += 0.0001f;

	return r;
}

float Utility::linearInterpolation(float a0, float b0, float a1, float b1, float t)
{
	float result;
	if (b1 > 0)
		result = (t * b0) / b1;
	else
		result = (((t - b1) * a0) / a1) + a0;
	return result;
}

