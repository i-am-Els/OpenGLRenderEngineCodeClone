#pragma once

#include <GL/glew.h>


class Material
{
public:
	Material();
	Material(float sIntensity, float shine);

	void UseMateial(unsigned int specularIntensityLocation, unsigned int shininessLocation);
	~Material();

private:
	float specularIntensity;
	float shininess;

};

