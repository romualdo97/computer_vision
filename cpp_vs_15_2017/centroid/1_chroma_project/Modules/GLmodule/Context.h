#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\..\configs.h"

class Context
{
public:
	// PROPERTIES
	GLFWwindow* window;

	// METHODS
	Context();
	bool createWindow();
	int windowShouldClose();
	void update();
	void terminate();
	~Context();
};

