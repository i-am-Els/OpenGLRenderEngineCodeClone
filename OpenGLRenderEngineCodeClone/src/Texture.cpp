#include "Texture.h"

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}



Texture::Texture(const char* fileLoc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = fileLoc;
}

void Texture::loadTexture()
{
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return ;
	}

	// Generate a Texture, like the VAO, VBO
	glGenTextures(1, &textureID);
	// We bind the Texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set up some parameters before loading in the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_TEXTURE_WRAP_S or _T defines the wrap axes, S -> x, T -> y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture parameter for when we zoom in on image, we minimize our image GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER for zooming out or magnifying
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR reduces pixelation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load in data for image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	// Generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

}

void Texture::loadTextureA()
{
	unsigned char* texData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLocation);
		return ;
	}

	// Generate a Texture, like the VAO, VBO
	glGenTextures(1, &textureID);
	// We bind the Texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Set up some parameters before loading in the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // GL_TEXTURE_WRAP_S or _T defines the wrap axes, S -> x, T -> y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture parameter for when we zoom in on image, we minimize our image GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER for zooming out or magnifying
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR reduces pixelation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load in data for image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	// Generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind the Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(texData);

}

void Texture::useTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::clearTexture()
{
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLocation = "";
}

Texture::~Texture()
{
	clearTexture();
}
