#pragma once

#include <opencv2\opencv.hpp>
#include <iostream>

namespace input
{
	void initCamera();
	void takePhoto();
	cv::Mat getPhoto();
	void releaseCamera();
}
