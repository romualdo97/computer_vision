#pragma once

#include <opencv2\opencv.hpp>

//#include <opencv2\imgproc.hpp>
//#include <opencv2\videoio.hpp>
//#include <iostream>

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

