#ifdef ChromaDLL_EXPORTS
#define CHROMADLL_API __declspec(dllexport)
#else
#define CHROMADLL_API __declspec(dllimport)
#endif // ChromaDLL_EXPORTS

#include "configs.h"
#include "input.h"
#include "segmentation.h"
#include "noisereduction.h"
#include "features.h"

void writeFrames(char * path, cv::Mat image);

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

	// NOISE REDUCTION MODULE
	CHROMADLL_API void reduceNoise();

	// FEATURES MODULE
	CHROMADLL_API void calculateCentroid();
	CHROMADLL_API double getCentroid_x();
	CHROMADLL_API double getCentroid_y();
	CHROMADLL_API double getNormCentroid_x();
	CHROMADLL_API double getNormCentroid_y();
}

