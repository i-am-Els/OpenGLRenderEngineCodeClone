#include "Window.h"

Window::Window()
{
    width = 800;
    height = 600;
    bufferWidth = 0, bufferHeight = 0;
    mainWindow = 0;

	// To initialize key array
	for (size_t i = 0; i < 1024; i++) 
	{
		keys[i] = 0;
	}
}


Window::Window(int windowWidth, int windowHeight)
{
    width = windowWidth;
    height = windowHeight;
    bufferWidth = 0, bufferHeight = 0;
    mainWindow = 0;

	// To initialize key array
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

int Window::initialize()
{
	// Initialize GLFW

	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...!\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// Opengl Version

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core profile = No Backwards Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow forward compaibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// Create Window

	mainWindow = glfwCreateWindow(width, height, "Main Window", NULL, NULL);

	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed...\n";
		glfwTerminate();
		return 1;
	}


	// OpenGl viewport dimensions
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// Handle key+mouse input
	createCallbacks();

	// Hide cursor
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialization failed!...\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Enable depth test to determine which trianlges are deeper into the image effectively and determine which should be drawn over the others 
	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

    return 0;
}

float Window::getXchange()
{
	float theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

float Window::getYchange()
{
	float theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

Window::~Window()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}


void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = (float)xPos;
		theWindow->lastY = (float)yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = (float)xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - (float)yPos;

	theWindow->lastX = (float)xPos;
	theWindow->lastY = (float)yPos;
}

void Window::setFrameBuffer(void (*func) (GLFWwindow*, int, int))
{
	glfwSetFramebufferSizeCallback(mainWindow, func);
}

