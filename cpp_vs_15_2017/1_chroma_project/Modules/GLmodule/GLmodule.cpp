#include "GLmodule.h"



GLmodule::GLmodule()
{
	std::cout << "Initializing GL module" << std::endl;
	// ==========================================================================================================
	// INIT GLFW AND PREPARE WINDOW AND CONTEXT CREATION
	glfwInit(); // init glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // request to create context for opengl 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // request to create context for opengl x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // request to create core profile context
	// ==========================================================================================================
}

int GLmodule::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

bool GLmodule::initContext()
{	
	// ==========================================================================================================
	// CREATE WINDOW AND MAKE ITS CONTEXT THE CURRENT
	window = glfwCreateWindow(W, H, TITLE, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window creation failed\n" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	// ==========================================================================================================

	// ==========================================================================================================
	// 3. MANAGES OPENGL FUNCTIONS POINTERS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n" << std::endl;
		return false;
	}
	return true;
	// ==========================================================================================================

	glViewport(0, 0, W, H);
}

void GLmodule::update()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
	glfwSwapBuffers(window); // swap opengl back and front buffers
	glfwPollEvents(); // listen for events
}

void GLmodule::terminate()
{
	glfwTerminate();
}

GLmodule::~GLmodule()
{
}