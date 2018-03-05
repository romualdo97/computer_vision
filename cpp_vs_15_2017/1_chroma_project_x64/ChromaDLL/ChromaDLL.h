#ifdef ChromaDLL_EXPORTS
#define CHROMADLL_API __declspec(dllexport)
#else
#define CHROMADLL_API __declspec(dllimport)
#endif // ChromaDLL_EXPORTS

#include "input.h"
#include "segmentation.h"

void writeFrames(char *path);

extern "C"
{
	// MISC FUNCTIONALITY
	CHROMADLL_API void updateCount();
	CHROMADLL_API void terminatePlugin();

	// INPUT MODULE
	CHROMADLL_API void initCamera();
	CHROMADLL_API void takePhoto();
	CHROMADLL_API void releaseCamera();
	
	// SEGMENTATION MODULE
	CHROMADLL_API void calibrate();
	CHROMADLL_API void calculateMask();
	CHROMADLL_API void terminateSegmentation();
}

