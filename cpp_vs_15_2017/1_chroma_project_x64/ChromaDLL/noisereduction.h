#pragma once

#include <opencv2\opencv.hpp>

namespace noiseReduction
{
	void process(cv::Mat& destFrame, cv::Mat inFrame, int iterations);
}