#include "input.h"

namespace input
{
	cv::VideoCapture capture;
	cv::Mat inputFrame;
	int i;
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
	std::stringstream imgname;
	imgname << "img/capture" << i << ".jpg";
	capture >> inputFrame;
	cv::flip(inputFrame, inputFrame, 1); // flip capture frame
	cv::imwrite(imgname.str(), inputFrame);
	i++;
}

cv::Mat input::getPhoto()
{
	return inputFrame;
}

void input::releaseCamera()
{
	capture.release();
	i = 0;
}
