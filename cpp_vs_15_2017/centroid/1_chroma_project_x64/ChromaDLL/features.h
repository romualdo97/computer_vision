#pragma once

#include <opencv2\opencv.hpp>

namespace features
{
	void calculateMoments(cv::Mat inFrame);
	double getCentroid_x();
	double getCentroid_y();
}