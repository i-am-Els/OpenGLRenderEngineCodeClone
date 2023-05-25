
#include "Utility.h"
float Utility::colorDistort(float r)
{
	if (r >= 1.0f)
		r = 0;
	r += 0.0001f;

	return r;
}

