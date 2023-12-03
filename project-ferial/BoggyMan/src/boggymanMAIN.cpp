
#include <iostream>
#include <sstream>
#define GLEW_STATIC
#include "GL/glew.h"	// Important - this header must come before glfw3 header
#include "GLFW/glfw3.h"
//my custom headers
#include "texture.h"
#include "ShaderProgram.h"
//transformation headers
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"
//Camera headers 
#include "Camera.h"
//obj loader 
#include "Mesh.h"

#include "Model.h"
using namespace std;
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
// Global Variables
const char* APP_TITLE = "Computer Graphics - Camera Demo";
const int gWindowWidth = 800;
const int gWindowHeight = 600;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;

//setting Camera
FPSCamera fpsCamera(glm::vec3(0.0f, 2.0f, 10.0));
const double ZOOM_SENSITIVITY = -3.0f;
const double MOVE_SPEED = 5.0f; //units per sec
const double MOUSE_SENSITIVITY = 0.1f;

// Function prototypes
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void showFPS(GLFWwindow* window);
bool initOpenGL();
int main()
{
    // glfw: initialize and configure
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
  /*  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }*/
    if (!initOpenGL())
    {
        // An error occured
        std::cerr << "GLFW initialization failed" << std::endl;
        return -1;
    }


    // build and compile shaders
    // -------------------------
    ShaderProgram shaderProgram;
    shaderProgram.loadShaders("res/shaders/Projection.vert", "res/shaders/Transform.frag");
    // load models
    // -----------
   // Model ourModel(FileSystem::getPath("resources/objects/backpack/backpack.obj"));
  //  Model model("res\models\ghost1.obj");
    
    Model model("res/models/ghost1.obj");

   

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    double lastTime = glfwGetTime();
    float cubeAngle = 0.0f;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(gWindow))
    {
        // per-frame time logic
        // --------------------
        showFPS(gWindow);

        //delta time of rendering
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        // Poll for and process events
        glfwPollEvents();
        update(deltaTime);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        shaderProgram.use();

        // view/projection transformations
        glm::mat4 view(1.0), projection(1.0);
        view = fpsCamera.getViewMatrix();

        projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / gWindowHeight, 0.1f, 100.0f);
        glm::vec3 viewPos;
        viewPos.x = fpsCamera.getPosition().x;
     
        shaderProgram.setUniform("view", view);
        shaderProgram.setUniform("projection", projection);
      
      //  ourShader.setMat4("model", model);
       // ourModel.Draw(ourShader);
 
        viewPos.x = fpsCamera.getPosition().x;
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
   
        //shaderProgram.setUniform("model", model);
      // ourModel.Draw(shaderProgram);

        model.Draw(shaderProgram);
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        //shaderProgram.setMat4("model", model);
        //ourModel.Draw(shaderProgram);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(gWindow);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

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
    fpsCamera.rotate(float(gWindowWidth / 2.0f - mouseX) * MOUSE_SENSITIVITY,
        float(gWindowHeight / 2.0f - mouseY) * MOUSE_SENSITIVITY);
    glfwSetCursorPos(gWindow, gWindowWidth / 2.0f, gWindowHeight / 2.0f);

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
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}