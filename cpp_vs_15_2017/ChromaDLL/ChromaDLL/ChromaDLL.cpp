#include "ChromaDLL.h"
#include "CVmodule\CVmodule.h"

CVmodule cmptrVision;

extern "C"
{
	float getNumber() // funcionando
	{
		return 21.0f;
	}
	void showCamera()
	{
		cmptrVision.update();
	}
	bool isCamera()
	{
		return cmptrVision.in.isCamera;
	}
}