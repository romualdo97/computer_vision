#pragma once

#include <opencv2\opencv.hpp>
#include <iostream>

namespace segmentation
{
	void getCalibrated(cv::Mat &destFrame, cv::Mat inFrame);
	void getMask(cv::Mat &destFrame, cv::Mat inFrame);

	void calibrate(cv::Mat inFrame);
	void calculateMask(cv::Mat inFrame);
	void terminate();
}