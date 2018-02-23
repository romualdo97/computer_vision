#include "Quad.h"



Quad::Quad()
{
	// generate buffers
	glGenVertexArrays(1, &VAO); // generate VAO
	glGenBuffers(1, &VBO); // generate VBO
	glGenBuffers(1, &EBO); // generate EBO
	
	// bind buffers
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	
	// set buffer data (pass data from CPU to GPU)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// assign "sense" to data in VBO buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0); // enable the vertex attribute in shader at location 0


	// unbind buffers
	//glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Quad::use()
{
	// load VAO context for draw quad
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Quad::~Quad()
{
}
