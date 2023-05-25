#include <GL/glew.h>

#pragma once
class Mesh
{
public:
	Mesh();
	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
	void RenderMesh();
	~Mesh();
private:
	unsigned int VAO, VBO, IBO, indexCount;
};



