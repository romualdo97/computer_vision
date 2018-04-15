#include "input.h"

namespace input
{
	cv::VideoCapture capture;
	cv::Mat inputFrame;
}

void input::initCamera()
{
	capture = cv::VideoCapture(0);
	if (!capture.isOpened())
	{
		std::cout << "Sorry, can´t use web cam.";
	}
}

void input::takePhoto()
{
	capture >> inputFrame;
	cv::flip(inputFrame, inputFrame, 1); // flip captured frame							 
}

cv::Mat input::getPhoto()
{
	takePhoto();
	return inputFrame;
}

void input::releaseCamera()
{
	capture.release();
}
