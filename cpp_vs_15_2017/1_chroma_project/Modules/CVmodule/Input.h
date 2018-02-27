#pragma once

#include <opencv2\opencv.hpp>

class Input
{
public:
	// PROPERTIES
	cv::Mat frame;
	cv::VideoCapture capture;
	bool isCamera = true;

	// METHODS
	Input();
	cv::Mat getFrame();
	cv::Mat getFrame_bw();
	~Input();
};

