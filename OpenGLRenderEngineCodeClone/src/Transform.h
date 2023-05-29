#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CommonValues.h"

class Transform
{
public:
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 dimension;

	glm::mat4 transformMatrix;

	Transform();
	Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	~Transform();

	void Translate(const glm::vec3& translationFactorV);
	void Rotate(const glm::vec3& rotationV);
	void Scale(const glm::vec3& scaleDimensionsV);

	void ResetTransform();
	void ResetTranslate();
	void ResetRotation();
	void ResetScale();
};

