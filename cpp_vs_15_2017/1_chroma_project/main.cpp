#include "Modules\GLmodule\GLmodule.h"

int main(void)
{
	GLmodule oceanScene;
	
	while (!oceanScene.shouldClose())
	{
		oceanScene.update(1.0f);
	}
	oceanScene.terminate();
	return 0;
}