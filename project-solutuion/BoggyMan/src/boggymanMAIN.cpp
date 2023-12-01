//-----------------------------------------------------------------------------
// BOO MAN - CMPS373 L51 PROJECT 
// FE1901981 - FATMA ALI ELBAKRY ELBADRAWY
// FM1706475 - FERIAL MOHAMMED ZAKARIA MARZOUK 
// DR. OSAMA HALABI AND T.A GEORGE YOUNES
//-----------------------------------------------------------------------------
#define GLEW_STATIC

#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ShaderProgram.h"

//***************TRANSFORMATION*****************
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

//***************CUSTOM HEADER******************
#include "Mesh.h"
//Camera headers 
#include "Camera.h"
//assimp obj loader
#include "ModelLoad.h"

// Global Variables
const char* APP_TITLE = "BOGGY MAN";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
const int numModels = 1;


//setting Camera [NEEDS VALUES MODIFICATIONS]
FPSCamera fpsCamera(glm::vec3(0.0f, 0.0f, 5.0), glm::vec3(1.0f, 1.0f, 1.0f));
const double ZOOM_SENSITIVITY = -3.0f;
const double MOVE_SPEED = 5.0f; //units per sec
const double MOUSE_SENSITIVITY = 0.1f;

// Function prototypes [NEEDS MODIFING]
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void showFPS(GLFWwindow* window);
bool initOpenGL();

//-----------------------------------------------------------------------------
// Main Application Entry Point
//-----------------------------------------------------------------------------
int main()
{

	//CHECKS IF INITIALIZATION WAS SUCCESSFUL
	if (!initOpenGL())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

	//CALLS SHADER PROGRAM(S)
	ShaderProgram shaderProgram;
	shaderProgram.loadShaders("res/shaders/Projection.vert", "res/shaders/Transform.frag");

	Mesh mesh[numModels];

	ModelLoad ghost1 = ModelLoad("res/models/ghost1.obj");
	for (const auto& mesh : meshes) {
		mesh.draw(shader);
	}

	//delta time of rendering 
	double lastTime = glfwGetTime();
	float cubeAngle = 0.0f;

	// Rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		showFPS(gWindow);

		//delta time of rendering
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		// Poll for and process events
		glfwPollEvents();
		update(deltaTime);

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render the quad (two triangles)
		shaderProgram.use();

		//projection
		glm::mat4 projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 100.0f);
		glm::mat4 view = fpsCamera.getViewMatrix();
		shaderProgram.setUniform("projection", projection);
		shaderProgram.setUniform("view", view);

		//render the models
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, 0.4f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));	// it's a bit too big for our scene, so scale it down
		shaderProgram.setUniform("model", model);
		ghost1.modelDraw(shaderProgram);

		// Swap front and back buffers
		glfwSwapBuffers(gWindow);

		lastTime = currentTime;
	}

	glfwTerminate();

	return 0;
}

//-----------------------------------------------------------------------------
// Initialize GLFW and OpenGL
//-----------------------------------------------------------------------------
bool initOpenGL()
{
	// Intialize GLFW 
	// GLFW is configured.  Must be called before calling any GLFW functions
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3

	// Create an OpenGL 3.3 core, forward compatible context window
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(gWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);

	//Enable depth testing 
	glEnable(GL_DEPTH_TEST);
	return true;
}

//-----------------------------------------------------------------------------
// Is called whenever a key is pressed/released via GLFW
//-----------------------------------------------------------------------------
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

//-----------------------------------------------------------------------------
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//-----------------------------------------------------------------------------
// Mouse Scroll function 
//-----------------------------------------------------------------------------
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITIVITY;
	fov = glm::clamp(fov, 1.0, 120.0); //eye sight range

	fpsCamera.setFOV((float)fov);
}

//-----------------------------------------------------------------------------
// Update function 
//-----------------------------------------------------------------------------
void update(double elapsedTime) {

	//camera orienatation
	double mouseX, mouseY;

	//get current mouse cursor position delta
	glfwGetCursorPos(gWindow, &mouseX, &mouseY);

	//rotate the camera using the delta in mouse differences, opposite left=> right vise versa 
	//fpsCamera.rotate(float(gWindowWidth / 2.0f - mouseX) * MOUSE_SENSITIVITY,
	//	float(gWindowHeight / 2.0f - mouseY) * MOUSE_SENSITIVITY);
	//glfwSetCursorPos(gWindow, gWindowWidth / 2.0f, gWindowHeight / 2.0f);

	//Camera movement  forward & backward
	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
	if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

	//left & Right
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());
	if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());

	//up & down
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * fpsCamera.getUp());
	if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move((float)MOVE_SPEED * (float)elapsedTime * -fpsCamera.getUp());

}

//-----------------------------------------------------------------------------
// Code computes the average frames per second, and also the average time it takes
// to render one frame.  These stats are appended to the window caption bar.
//-----------------------------------------------------------------------------
void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates to 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reset for next average.
		frameCount = 0;
	}

	frameCount++;
}