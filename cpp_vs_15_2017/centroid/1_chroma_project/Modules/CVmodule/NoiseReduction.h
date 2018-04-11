#pragma once
// read docs at: https://docs.opencv.org/2.4/doc/tutorials/imgproc/erosion_dilatation/erosion_dilatation.html
// how use morph functions?: https://stackoverflow.com/questions/17329932/how-to-use-erode-and-dilate-function-in-opencv

#include <opencv2\opencv.hpp>
//#include <opencv2\imgproc.hpp>

class NoiseReduction
{
public:
	// PROPERTIES
	cv::Mat frame;

	// METHODS
	NoiseReduction();
	void process(cv::Mat& destFrame, cv::Mat inFrame, int iterations);
	~NoiseReduction();

private:
	// PROPERTIES
	int erosion_size = 20;
	int dilation_size = 0;

	// METHODS
	void applyOpening(cv::Mat inFrame, int iterations);
	void applyClosing(cv::Mat inFrame, int iterations);
	void calculateErosion(cv::Mat inFrame, int iterations);
	void calculateDilation(cv::Mat inFrame, int iterations);
};

