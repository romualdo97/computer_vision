#include "face_tracker.h"


FACETRACKERLIB_API char * sayHello()
{
	return (char*)"hello world from dll";
}

FACETRACKERLIB_API void init()
{
	cv::VideoCapture cap(0);
	// check if camera is available
	if (!cap.isOpened())
	{
		std::cout << "Sorry, can't use webcam" << std::endl;
		return;
	}
	cv::Mat videoFrame;
	cap >> videoFrame;
	cv::imwrite("out.jpg", videoFrame);
	cap.release();
}
