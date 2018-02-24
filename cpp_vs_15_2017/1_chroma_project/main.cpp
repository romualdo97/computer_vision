#include "Modules\GLmodule\GLmodule.h"
#include "Modules\GLmodule\Quad.h"
#include "Modules\GLmodule\Shader.h"

int main(void)
{
	GLmodule GLapp;
	GLapp.initContext();
	Quad myQuad;
	//Shader basicShader("Modules/GLModule/Shaders/basic");
	Shader seascapeShader("Modules/GLModule/Shaders/seascape");
	
	double *mouse = (double*)malloc(2*sizeof(double));
	while (!GLapp.windowShouldClose())
	{
		// rgb(104, 109, 224)
		glClearColor(104.0f/255.0f, 109.0f/255.0f, 224.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//basicShader.use();
		seascapeShader.use();
		

		int iTimeLoc = glGetUniformLocation(seascapeShader.ID, "iTime");
		glUniform1f(iTimeLoc, (float)glfwGetTime());


		int iResolutionLoc = glGetUniformLocation(seascapeShader.ID, "iResolution");
		glUniform2f(iResolutionLoc, W, H);		


		glfwGetCursorPos(GLapp.window, mouse, mouse + 1);
		int iMouseLoc = glGetUniformLocation(seascapeShader.ID, "iMouse");
		glUniform2f(iMouseLoc, (float)(*mouse), (float)*(mouse+1));


		myQuad.use();

		GLapp.update();
	}
	GLapp.terminate();
	free(mouse);
	return 0;
}