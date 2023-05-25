#include "Light.h"

Light::Light()
{
	colour = glm::vec3(0.750f, 0.75f, 0.0f);
	ambientIntensity = 1.5f;
	diffuseIntensity = 0.0f;
}

Light::Light(float red, float green, float blue, float aIntensity, float dIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
}

Light::~Light()
{
}



