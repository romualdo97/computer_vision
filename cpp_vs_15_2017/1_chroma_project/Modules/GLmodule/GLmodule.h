/*
This module is responsible for vizualisation tasks
and interactive 3D app
*/

#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "..\..\configs.h"
class GLmodule
{
public:
	// PROPERTIES
	GLFWwindow* window;

	// METHODS
	GLmodule();
	int windowShouldClose();
	bool initContext();
	void update();
	void terminate();
	~GLmodule();
};

