#pragma once

#include <opencv2\opencv.hpp>
#include <iostream>
#include "configs.h"

namespace input
{
	void initCamera();
	void takePhoto();
	cv::Mat getPhoto();
	void releaseCamera();
}
