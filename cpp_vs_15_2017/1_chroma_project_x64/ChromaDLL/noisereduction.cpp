#include "noisereduction.h"

namespace noiseReduction
{
	cv::Mat frame;
}

void noiseReduction::process(cv::Mat & destFrame, cv::Mat inFrame, int iterations)
{
	cv::erode(inFrame, frame, cv::Mat(), cv::Point(-1, -1), iterations, 1, 1);
	destFrame = frame;
}