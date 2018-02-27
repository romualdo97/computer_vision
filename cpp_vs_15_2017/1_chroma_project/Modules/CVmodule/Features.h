#pragma once

// use of moments function: http://answers.opencv.org/question/460/finding-centroid-of-a-mask/

#include <opencv2\opencv.hpp>

class Features
{
public:
	// PROPERTIES
	double *centroid;
	double *normCentroid;
	cv::Moments moments;

	// METHODS
	Features();
	double *calculateCentroid(cv::Mat inFrame);
	double *calculateNormCentroid(cv::Mat inFrame);
	~Features();
};

