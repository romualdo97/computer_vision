#include "Context.h"



Context::Context()
{
	std::cout << "Initializing GL context" << std::endl;
	// ==========================================================================================================
	// INIT GLFW AND PREPARE WINDOW AND CONTEXT CREATION
	glfwInit(); // init glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // request to create context for opengl 3.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // request to create context for opengl x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // request to create core profile context
	// ==========================================================================================================

	createWindow();
}

bool Context::createWindow()
{
	// ==========================================================================================================
	// CREATE WINDOW AND MAKE ITS CONTEXT THE CURRENT
	window = glfwCreateWindow(rjlvmj_W, rjlvmj_H, rjlvmj_TITLE, NULL, NULL);
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

	glViewport(0, 0, rjlvmj_W, rjlvmj_H);
}

int Context::windowShouldClose()
{
	return glfwWindowShouldClose(window);
}

void Context::update()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_Q))
	{
		glfwSetWindowShouldClose(window, true);
	}
	glfwSwapBuffers(window); // swap opengl back and front buffers
	glfwPollEvents(); // listen for events
}

void Context::terminate()
{
	glfwTerminate();
}

Context::~Context()
{}