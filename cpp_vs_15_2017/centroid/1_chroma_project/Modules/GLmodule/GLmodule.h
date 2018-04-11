/*
This module is responsible for vizualisation tasks
and interactive 3D app
*/

#pragma once

// read about framebuffer target here: https://gamedevelopment.tutsplus.com/tutorials/how-to-write-a-smoke-shader--cms-25587

// helper libraries
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

// interactive 3d app dependencies (My OpenGL App)
#include "Context.h"
#include "Quad.h"
#include "Shader.h"

class GLmodule
{
public:
	// PROPERTIES
	Context windowContext;
	Quad myQuad;
	Shader myShader;
	double *mouse;


	// METHODS
	GLmodule();
	/*
	Draws the ocean scene
		@dayHour determines the sky color
		(receives a value in the range [0, 1])
	*/
	void update(float dayHour);
	int shouldClose();
	void terminate();
	~GLmodule();
};

