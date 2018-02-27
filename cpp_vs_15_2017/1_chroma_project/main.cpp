//#include <opencv2\opencv.hpp>
#include "Modules\CVmodule\CVmodule.h" // this must be included before GLmodule, posible opengl context conflicts
#include "Modules\GLmodule\GLmodule.h"



int main(void)
{
	GLmodule oceanScene;
	CVmodule cmptrVision;

	
	while (!oceanScene.shouldClose())
	{
		cmptrVision.update();
		oceanScene.update((float)*cmptrVision.normalizedCentroid);
	}
	oceanScene.terminate();
	return 0;
}