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
	capture >> inputFrame;
	cv::flip(inputFrame, inputFrame, 1); // flip capture frame
	
#ifdef rjlvmj_DEBUG_MODE
	// save image
	std::stringstream imgname;
	imgname << "img/capture" << i << ".jpg";
	cv::imwrite(imgname.str(), inputFrame);
	i++;
#endif // rjlvmj_DEBUG_MODE									 
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
