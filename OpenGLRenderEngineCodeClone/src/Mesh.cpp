#include "Mesh.h"
#include "CommonValues.h"

Mesh::Mesh()
{
	VAO = 0, VBO = 0, IBO = 0, indexCount = 0;
}

void Mesh::CreateMesh(float* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vertexStride)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices * sizeof(indices[0]), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * vertexStride, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * vertexStride, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);// Enabling vertex attribute pointers is done here beccause we are rendering only ine kind of mesh, it would rather be done in the renderMesh function if we are working dynamically.
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * vertexStride, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// Unbind the VBOs and VAOs
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// You should unbind IBO/EBO after you unbind the VAO!
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::RenderMesh()
{
	// Bind all arrays and buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Draw
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	// Unbind all arrays and buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//transformMatrix = glm::identity<glm::mat4>();
}

//void Mesh::Transform(glm::vec3 translationFactorV,
//							float degrees, glm::vec3 axisOfRotation,
//							glm::vec3 scaleDimensionsV)
//{
//	transformMatrix = Translate(transformMatrix, translationFactorV);
//	transformMatrix = Rotate(transformMatrix, degrees, axisOfRotation);
//	transformMatrix = Scale(transformMatrix, scaleDimensionsV);
//}
//
//glm::mat4 Mesh::Translate(glm::mat4 &model, const glm::vec3& translationFactorV)
//{
//	return glm::translate(model, translationFactorV);
//}
//
//glm::mat4 Mesh::Rotate(glm::mat4& model, const float degrees, const glm::vec3& axisOfRotation)
//{
//	return glm::rotate(model, degrees * TO_RADIANS, axisOfRotation);
//}
//
//glm::mat4 Mesh::Scale(glm::mat4& model, const glm::vec3& scaleDimensionsV)
//{
//	return glm::scale(model, scaleDimensionsV);
//}

Mesh::~Mesh()
{
}


