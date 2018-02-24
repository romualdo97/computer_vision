#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Quad
{
public:
	// PROPERTIES 
	unsigned int VAO, VBO, EBO;

	// quad vertex data in clock-wise orientation
	float data[20] = {
		// vertices							uv (texture coordinates)
		0.8f, 0.8f, 0.0, /*right top*/		1.0, 1.0,
		0.8f, -0.8f, 0.0, /*righ bottom*/	1.0, 0.0,
		-0.8f, -0.8f, 0.0, /*left bottom*/	0.0, 0.0,
		-0.8f, 0.8f, 0.0, /*left top*/		0.0, 1.0	
	};

	// indices for EBO index drawing
	unsigned int indices[6] = {
		0, 3, 1,
		3, 2, 1
	};

	// METHODS
	Quad();
	void use();
	~Quad();
};

