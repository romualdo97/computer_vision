#include "segmentation.h"

// PROPERTIES
namespace segmentation
{
	cv::Mat frame;
	cv::Mat calibratedFrame;
	bool isCalibrating = true;
	int n = FRAMES_FOR_CALIBRATION;
	float _a = 1.0f / (float)n;
	int index = 0;
}

void segmentation::getCalibrated(cv::Mat & destFrame, cv::Mat inFrame)
{
	if (isCalibrating) calibrate(inFrame);

	//calculateMask(inFrame);

	destFrame = calibratedFrame;
}

void segmentation::getMask(cv::Mat & destFrame, cv::Mat inFrame)
{
	calculateMask(inFrame);
	destFrame = frame;
}

void segmentation::calibrate(cv::Mat inFrame)
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
	//index += 0;// for debug purposes
}

void segmentation::calculateMask(cv::Mat inFrame)
{
	// GET MASK
	cv::absdiff(calibratedFrame, inFrame, frame);
	cv::threshold(frame, frame, 25, 255, CV_THRESH_BINARY);
}

void segmentation::terminate()
{
	calibratedFrame = cv::Mat();
	isCalibrating = true;
	index = 0;
}
