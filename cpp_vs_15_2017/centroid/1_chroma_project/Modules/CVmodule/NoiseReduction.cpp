#include "NoiseReduction.h"




NoiseReduction::NoiseReduction()
{
}

void NoiseReduction::process(cv::Mat & destFrame, cv::Mat inFrame, int iterations)
{
	calculateErosion(inFrame, iterations);
	destFrame = frame;
}

NoiseReduction::~NoiseReduction()
{
}

void NoiseReduction::applyOpening(cv::Mat inFrame, int iterations)
{
	calculateErosion(inFrame, iterations);
	calculateDilation(inFrame, iterations);
	inFrame = frame;
}

void NoiseReduction::applyClosing(cv::Mat inFrame, int iterations)
{
	calculateDilation(inFrame, iterations);
	calculateErosion(inFrame, iterations);
	inFrame = frame;
}


void NoiseReduction::calculateErosion(cv::Mat inFrame, int iterations)
{	
	cv::erode(inFrame, frame, cv::Mat(), cv::Point(-1, -1), iterations, 1, 1);
}

void NoiseReduction::calculateDilation(cv::Mat inFrame, int iterations)
{
	cv::dilate(inFrame, frame, cv::Mat(), cv::Point(-1, -1), iterations, 1, 1);
}
