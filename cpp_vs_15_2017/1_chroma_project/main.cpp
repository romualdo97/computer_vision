//#include <opencv2\opencv.hpp>
#include "Modules\CVmodule\CVmodule.h" // this must be included before GLmodule, posible opengl context conflicts
#ifdef rjlvmj_SHOW_OPENGL_APP
#include "Modules\GLmodule\GLmodule.h"
#endif // rjlvmj_SHOW_OPENGL_APP

int main(void)
{
	CVmodule cmptrVision;
	
#ifndef rjlvmj_SHOW_OPENGL_APP
	while (true)
	{
		cmptrVision.update();
		if (cv::waitKey(30) == 'q')
		{
			break;
		}
	}
#endif // rjlvmj_SHOW_OPENGL_APP

#ifdef rjlvmj_SHOW_OPENGL_APP
	GLmodule oceanScene;
	while (!oceanScene.shouldClose())
	{
		cmptrVision.update();
		oceanScene.update((float)*cmptrVision.normalizedCentroid);
	}
	oceanScene.terminate();
#endif // rjlvmj_SHOW_OPENGL_APP
	return 0;
}