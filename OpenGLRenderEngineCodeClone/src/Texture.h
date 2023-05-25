#pragma once

#include <GL/glew.h>

#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	void loadTexture();
	void loadTextureA();
	void useTexture();
	void clearTexture();


	~Texture();

private:
	unsigned int textureID;
	int width, height, bitDepth;
	
	const char* fileLocation;
};

