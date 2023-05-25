#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, float startYaw, float startPitch, float startMoveSpeed, float startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, float deltaTime)
{
	float velocity = moveSpeed * deltaTime;
	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
}

void Camera::mouseControl(float xChangeScreen, float yChangeScreen, float deltaTime)
{
	xChangeScreen *= turnSpeed * deltaTime;
	yChangeScreen *= turnSpeed * deltaTime;

	yaw += xChangeScreen;
	pitch += yChangeScreen;

	// make sure pitch is constrained and your head can't move 360 degrees
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	// set front to move forward in our new forward direction that we are looking at not ground forward
	update();
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::mat4 Camera::calculateViewMatrix()
{
	// you can set the 'center' to a model position if for example you want camera to follow the model about in a 3rd person game
	return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


