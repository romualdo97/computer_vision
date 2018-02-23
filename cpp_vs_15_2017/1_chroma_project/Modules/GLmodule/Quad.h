#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Quad
{
public:
	// PROPERTIES 
	unsigned int VAO, VBO, EBO;

	// quad vertex data in clock-wise orientation
	float vertices[12] = {
		0.5, 0.5, 0.0, // right top
		0.5, -0.5, 0.0, // righ bottom
		-0.5, -0.5, 0.0, // left bottom
		-0.5, 0.5, 0.0 // left top
	};

	// indices for EBO index drawing 
	/*unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};*/
	unsigned int indices[6] = {
		0, 3, 1,
		3, 2, 1
	};

	// METHODS
	Quad();
	void use();
	~Quad();
};

