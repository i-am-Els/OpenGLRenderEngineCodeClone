// the define statement below must be used in other for the stb_image header file to work as a code file
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include"CommonValues.h"

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"



 
const float toRadians = 3.14159265f / 180.0f;

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

//Material shinyMaterial;
//Material dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];

float deltaTime = 0.0f;
float lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "src/Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "src/Shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indicesCount, float* vertices, unsigned int verticesCount, unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indicesCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;		// select the vertex position coordinates for the current indices
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 0]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 0]);

		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset; // jump to the normal part of the vertices
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;

	}

	for (size_t i = 0; i < verticesCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1, // left side triangle
		1, 3, 2, // right side triangle
		2, 3, 0, // front side triangle
		0, 1, 2  // base triangle
	};

	float vertices[] = {
	//		x		y		z		u		v		normal x, y, z
		-1.0f,	-1.0f,	-0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f,	-1.0f,	1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f,	-1.0f,	-0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f,	1.0f,	0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	float floorVertices[] = {
		-10.0f, 0.0f,	-10.0f,		0.0f, 0.0f,		 0.0f, -1.0f, 0.0f,
		10.0f,	0.0f,	-10.0f,		10.0f, 0.0f,	 0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f,	10.0f,		0.0f,10.0f,		 0.0f, -1.0f, 0.0f,
		10.0f,	0.0f,	10.0f,		10.0f, 10.0f, 	 0.0f, -1.0f, 0.0f
	};

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	
	Mesh* obj1 = new  Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new  Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new  Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


int main()
{
	Window mainWindow;
	mainWindow.initialize();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), - 90.0f, 0.0f, 5.0f, 0.1f);

	brickTexture = Texture("src/Textures/brick.png");
	brickTexture.loadTextureA();
	dirtTexture = Texture("src/Textures/dirt.png");
	dirtTexture.loadTextureA();
	plainTexture = Texture("src/Textures/plain.png");
	plainTexture.loadTextureA();

	Material shinyMaterial(.0f, 32.0f);
	Material dullMaterial(0.3f, 4.0f);

	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 
								0.1f, 0.3f,
								0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,
								0.1f, 1.0f,
								4.0f, 0.0f, 0.0f,
								0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
								0.1f, 0.0f,
								-4.0f, 2.0f, 0.0f,
								0.3f, 0.1f, 0.1f);
	pointLightCount++;

	unsigned int uniformModel = 0, uniformProjection = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;

	glm::mat4 projection = glm::perspective(45.0f, (float)mainWindow.getBufferWidth() / (float)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		mainWindow.setFrameBuffer(&frame_buffer_size_callback);
		// deltaTime calculate now
		float now = (float)glfwGetTime();

		deltaTime = now - lastTime;
		lastTime = now;

		// Get and handle user input events
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());

		// Clear window screen
		glClearColor(0.1f, 0.1f, 0.1f, 0.03f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation(); 

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
 		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::mat4 model = glm::identity<glm::mat4>();

		glm::mat3 reflectMat(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = model * glm::mat4(reflectMat);
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		brickTexture.useTexture();
		shinyMaterial.UseMateial(uniformSpecularIntensity, uniformShininess);
		meshList[0]->RenderMesh();

		model = glm::identity<glm::mat4>();
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -2.5f));
		model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		dirtTexture.useTexture();
		dullMaterial.UseMateial(uniformSpecularIntensity, uniformShininess);
		meshList[1]->RenderMesh();

		model = glm::identity<glm::mat4>();
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::rotate(model, 15 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		plainTexture.useTexture();
		shinyMaterial.UseMateial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();
		



		glUseProgram(0);
		mainWindow.swapBuffers();

	}


	return 0;

}


