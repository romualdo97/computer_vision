#include "GLmodule.h"



GLmodule::GLmodule()
{
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
	myShader.setVec2("iResolution", W, H); // pass resolution to shader
	glfwGetCursorPos(windowContext.window, mouse, mouse + 1); // get mouse position
	myShader.setVec2("iMouse", (float)*mouse, (float)*(mouse + 1)); // pass mouse position
	myShader.setFloat("iDayHour", dayHour);
	myShader.setFloat("iDir", 0.0);

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