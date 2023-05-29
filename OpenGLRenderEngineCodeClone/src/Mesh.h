#include <GL/glew.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>


#pragma once
class Mesh
{
public:
	glm::mat4 transformMatrix = glm::identity<glm::mat4>();
	Mesh();
	void CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vertexStride);
	void RenderMesh();
	/*void Transform(glm::vec3 translationFactorV,
						float degrees, glm::vec3 axisOfRotation,
						glm::vec3 scaleDimensionsV);*/
	~Mesh();
private:
	unsigned int VAO, VBO, IBO, indexCount;
	/*static glm::mat4 Translate(glm::mat4& model, const glm::vec3& translationFactorV);
	static glm::mat4 Rotate(glm::mat4& model, const float degrees, const glm::vec3& axisOfRotation);
	static glm::mat4 Scale(glm::mat4& model, const glm::vec3& scaleDimensionsV);*/
};
