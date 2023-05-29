#include "Transform.h"

Transform::Transform()
{
	position = glm::vec3(0.0f);
	orientation = glm::vec3(0.0f);
	dimension = glm::vec3(1.0f);

	transformMatrix = glm::identity<glm::mat4>();

}

Transform::Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	position = pos;
	orientation = rot;
	dimension = scale;

	transformMatrix = glm::identity<glm::mat4>(); 

	Translate(position);
	Rotate(orientation);
	Scale(dimension);
}

void Transform::Translate(const glm::vec3& position)
{
	this->position = position;
	transformMatrix = glm::translate(transformMatrix, position);
}

void Transform::Rotate(const glm::vec3& rotation)
{
	this->orientation = rotation;
	for (size_t i = 0; i < rotation.length(); i++)
	{
		switch (i) {
		case 0:
			transformMatrix = glm::rotate(transformMatrix, rotation.x * TO_RADIANS, glm::vec3(1.0f, 0.0f, 0.0f));
			continue;
		case 1:
			transformMatrix = glm::rotate(transformMatrix, rotation.y * TO_RADIANS, glm::vec3(0.0f, 1.0f, 0.0f));
			continue;
		case 2:
			transformMatrix = glm::rotate(transformMatrix, rotation.z * TO_RADIANS, glm::vec3(0.0f, 0.0f, 1.0f));
			continue;
		default:
			transformMatrix = glm::rotate(transformMatrix, rotation.x * TO_RADIANS, glm::vec3(1.0f, 1.0f, 1.0f));
			continue;
		}
	}
}

void Transform::Scale(const glm::vec3& dimension)
{
	this->dimension = dimension;
	transformMatrix = glm::scale(transformMatrix, dimension);
}

void Transform::ResetTransform()
{
	transformMatrix = glm::identity<glm::mat4>();
	position = glm::vec3(0.0f);
	orientation = glm::vec3(0.0f);
	dimension = glm::vec3(1.0f);
}

void Transform::ResetTranslate()
{
	Translate(glm::vec3(0.0f));
}

void Transform::ResetRotation()
{
	Rotate(glm::vec3(0.0f));
}

void Transform::ResetScale()
{
	Scale(glm::vec3(1.0f));
}

Transform::~Transform()
{
}
