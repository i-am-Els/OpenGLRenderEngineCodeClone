#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class Window
{
public:
	Window();
	Window(int windowWidth, int windowHeight);

	int initialize();
	
	int getBufferWidth() { return bufferWidth; }
	int getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	float getXchange();
	float getYchange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }
	 
	void setFrameBuffer(void (*func) (GLFWwindow*, int, int));
	~Window();
private:
	GLFWwindow* mainWindow;
	int width, height;
	int bufferWidth, bufferHeight;

	bool keys[1024];

	float lastX;
	float lastY;
	float xChange;
	float yChange;
	bool mouseFirstMoved;


	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

