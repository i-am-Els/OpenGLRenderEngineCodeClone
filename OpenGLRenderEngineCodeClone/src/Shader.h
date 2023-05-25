#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"

#pragma once
class Shader
{
public:
	Shader();
	void CreateFromFiles(const char* vShader, const char* fShader);
	std::string readShaderCodeFromFile(const char* shaderPath);
	void UseShader() { glUseProgram(this->shader); }
	unsigned int GetModelLocation() { return this->uniformModel; }
	unsigned int GetProjectionLocation() { return this->uniformProjection; }
	unsigned int GetViewLocation() { return this->uniformView; }
	unsigned int GetAmbientIntensityLocation() { return uniformDirectionalLight.uniformAmbientIntensity; }
	unsigned int GetAmbientColourLocation() { return uniformDirectionalLight.uniformColour; }
	unsigned int GetDiffuseIntensityLocation() { return uniformDirectionalLight.uniformDiffuseIntensity; }
	unsigned int GetDirectionLocation() { return uniformDirectionalLight.uniformDirection; }
	unsigned int GetSpecularIntensityLocation() { return this->uniformSpecularIntensity; }
	unsigned int GetShininessLocation() { return this->uniformShininess; }
	unsigned int GetEyePositionLocation() { return this->uniformEyePosition; }

	void SetDirectionalLight(DirectionalLight* theLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);

	~Shader();

private:
	int pointLightCount;
	unsigned int shader, uniformModel, uniformProjection, uniformView, uniformEyePosition,
		uniformSpecularIntensity, uniformShininess;

	struct DRLight{
		unsigned int uniformColour;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity; 
		unsigned int uniformDirection;
	} uniformDirectionalLight;

	unsigned int uniformPointLightCount;

	struct PTLight{
		unsigned int uniformColour;
		unsigned int uniformAmbientIntensity;
		unsigned int uniformDiffuseIntensity;

		unsigned int uniformPosition;
		unsigned int uniformConstant;
		unsigned int uniformLinear;
		unsigned int uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];
	
	void addShader(unsigned int theProgram, const char* shaderCode, GLenum shaderType);
	void compileShaders(const char* vShaderCode, const char* fShaderCode);
};



