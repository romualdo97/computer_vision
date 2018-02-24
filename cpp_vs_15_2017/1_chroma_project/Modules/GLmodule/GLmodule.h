/*
This module is responsible for vizualisation tasks
and interactive 3D app
*/

#pragma once

// read about framebuffer target here: https://gamedevelopment.tutsplus.com/tutorials/how-to-write-a-smoke-shader--cms-25587

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

