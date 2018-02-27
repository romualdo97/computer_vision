#pragma once

#include <opencv2\opencv.hpp>
#include "..\..\configs.h"


class Segmentation
{
public:
	// METHODS
	Segmentation();
	void process(cv::Mat &destFrame, cv::Mat inFrame);
	~Segmentation();

private:
	
	// PROPERTIES
	cv::Mat frame;
	cv::Mat calibratedFrame;
	cv::Mat calibrtd;
	bool isCalibrating = true;
	int n;
	float _a;
	int index;

	// METHODS
	void calibrate(cv::Mat inFrame);
	void calculateMask(cv::Mat inFrame);
};

