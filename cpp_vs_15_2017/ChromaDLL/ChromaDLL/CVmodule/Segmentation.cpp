#include "Segmentation.h"



Segmentation::Segmentation()
{
	n = FRAMES_FOR_CALIBRATION;
	_a = 1.0f / n;
	index = 0;
}

void Segmentation::process(cv::Mat &destFrame, cv::Mat inFrame)
{	
	if (isCalibrating) calibrate(inFrame);

	calculateMask(inFrame);

	destFrame = frame;	
}

Segmentation::~Segmentation()
{
}


void Segmentation::calibrate(cv::Mat inFrame)
{
	std::cout << "calibrate function is being executed" << std::endl;
	// CALIBRATE
	if (index < n)
	{
		//nFrames.push_back(inFrame);
		calibratedFrame = calibratedFrame + _a * inFrame;

#ifdef DEBUG_MODE
		std::stringstream winName;
		winName << "average at frame " << index << " (calibration)";
		cv::imshow(winName.str(), calibratedFrame);
#endif // DEBUG_MODE
	}
	else
	{
		std::cout << "\tsetting isCalibrating = false" << std::endl;
		isCalibrating = false;
	}
	index++;
	index += 0;// for debug purposes

}

void Segmentation::calculateMask(cv::Mat inFrame)
{
	// GET MASK
	cv::absdiff(calibratedFrame, inFrame, frame);
	cv::threshold(frame, frame, 25, 255, CV_THRESH_BINARY);
}
