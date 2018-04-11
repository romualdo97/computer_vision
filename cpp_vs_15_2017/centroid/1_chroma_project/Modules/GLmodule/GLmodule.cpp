#include "GLmodule.h"



GLmodule::GLmodule()
{
	std::cout << "\n\nInitializing GL module" << std::endl;
	myShader = Shader("Modules/GLmodule/Shaders/seascape");
	mouse = (double*)malloc(2 * sizeof(double));
}

void GLmodule::update(float dayHour)
{
	// clear color buffer - rgb(104, 109, 224)
	glClearColor(104.0f / 255.0f, 109.0f / 255.0f, 224.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// use shader
	myShader.use();

	// pass uniforms
	myShader.setFloat("iTime", (float) glfwGetTime()); // pass time to shader
	myShader.setVec2("iResolution", rjlvmj_W, rjlvmj_H); // pass resolution to shader
	glfwGetCursorPos(windowContext.window, mouse, mouse + 1); // get mouse position
	myShader.setVec2("iMouse", (float)*mouse, (float)*(mouse + 1)); // pass mouse position
	myShader.setFloat("iDayHour", dayHour);

	float output_end = -1.0f;
	float output_start = 1.0f;
	float input_end = 1.0f;
	float input_start = 0.0f;
	float input = dayHour;
	float slope = (output_end - output_start) / (input_end - input_start);
	float _output = output_start + slope * (input - input_start);


	/*if (dayHour > 0.7)
		myShader.setFloat("iDir", 1.0);
	else
		myShader.setFloat("iDir", 0.0);*/
	myShader.setFloat("iDir", _output);
	
	// draw quad
	myQuad.use();

	// update the window context
	windowContext.update();
}

int GLmodule::shouldClose()
{
	return windowContext.windowShouldClose();
}

void GLmodule::terminate()
{
	glfwTerminate();
	free(mouse);
}

GLmodule::~GLmodule()
{
}