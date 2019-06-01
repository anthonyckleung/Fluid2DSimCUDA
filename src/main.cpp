#include <iostream>

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Grid2D.hpp"
#include "Simulation.h"
#include "ResourceManager.h"



const char  * APP_TITLE     = "FluidSim";
const GLuint  SCREEN_WIDTH  = 400;
const GLuint  SCREEN_HEIGHT = 400;
GLFWwindow	* gWindow       = NULL; //pointer to a window
Simulation    simulation(SCREEN_WIDTH, SCREEN_HEIGHT);

bool		  initOpenGL();
ArrayXs  x(3, 3);



// Test out grid template
//Grid2D<double>  gridtemp = Grid2D<double>(SCREEN_HEIGHT, SCREEN_WIDTH);
//Grid2D<double>  gridtemp2 = Grid2D<double>(SCREEN_HEIGHT, SCREEN_WIDTH);

int main()
{
	x << 1, 2, 3,
		5, 4, 16,
		7, 8, 9;
	//std::cout << x(1,2) << std::endl;
	//std::cout << gridtemp(1,3) << std::endl;
	//std::cout << gridtemp(1, 3) + gridtemp2(4,2) << std::endl;
	//gridtemp.clear();
	//std::cout << gridtemp.data() << std::endl;
	//std::cout << gridtemp.data() + 1* gridtemp.rows() *gridtemp.cols() << std::endl;
	if (!initOpenGL())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

	// OpenGL configuration
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize Simulation
	std::cout << "Initializing simulation..." << std::endl;
	simulation.Initialize();
	simulation.m_State = SIM_ACTIVE;
	std::cout << "Simulation Initialized..." << std::endl;

	// Render Loop
	while (!glfwWindowShouldClose(gWindow))
	{
		// Poll and process events
		glfwPollEvents();

		// Clear the screen (color and depth buffers)
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		simulation.Render();

		glfwSwapBuffers(gWindow); //This should avoid flickering
	}
	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();


	glfwTerminate();//Shut down GLFW

	return 0;
}



void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


bool initOpenGL()
{
	//Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	//Setting (minimum) OpenGL version (ver. 3.3 here)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//Force to call modern methods (i.e., cannot call old methods)
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	gWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, APP_TITLE, NULL, NULL);

	if (!gWindow)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); //Let GLFW clean up properly
		return false;
	}

	glfwMakeContextCurrent(gWindow); //make pWindow the current window
	glfwSetKeyCallback(gWindow, glfw_onKey);

	glewExperimental = GL_TRUE; //Need to initalize to ensure modern openGL is set up properly
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}

	return true;
	
}
