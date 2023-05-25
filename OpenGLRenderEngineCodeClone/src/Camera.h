#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed);
	
	void keyControl(bool* keys, float deltaTime);
	void mouseControl(float xChangeScreen, float yChangeScreen, float deltaTime = 1.0f);

	glm::vec3 getCameraPosition();

	glm::mat4 calculateViewMatrix();
	
	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw;
	float pitch;

	float moveSpeed;
	float turnSpeed;

	void update();
};
