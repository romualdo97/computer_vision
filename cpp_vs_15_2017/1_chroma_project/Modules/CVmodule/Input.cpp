#include "Input.h"



Input::Input()
{
	capture = cv::VideoCapture(0);
	if (!capture.isOpened())
	{
		std::cout << "Sorry, can´t use web cam.";
		isCamera = false;
	}
}

cv::Mat Input::getFrame()
{
	if (!isCamera) return cv::Mat::zeros(cv::Size(10, 10), 0);
	capture >> frame;
	cv::flip(frame, frame, 1);
	return frame;
}

cv::Mat Input::getFrame_bw()
{
	getFrame();
	cv::cvtColor(frame, frame, CV_RGB2GRAY);

	return frame;
}

Input::~Input()
{	
	
}
