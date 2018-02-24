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


	
	while (!GLapp.windowShouldClose())
	{
		// rgb(104, 109, 224)
		glClearColor(104.0/255.0, 109.0/255.0, 224.0/255.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		//basicShader.use();
		seascapeShader.use();
		myQuad.use();

		GLapp.update();
	}
	GLapp.terminate();
	return 0;
}