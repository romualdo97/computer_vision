#pragma once
// include opencv
#include <opencv2\opencv.hpp>
// include dlib
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\opencv\cv_image.h>
// include standards
#include <iostream>

#ifdef FACETRACKERLIB_EXPORTS
#define FACETRACKERLIB_API __declspec(dllexport)
#else
#define FACETRACKERLIB_API __declspec(dllimport)
#endif // FACETRACKERLIB_EXPORTS

#define DOWNSAMPLE_RATIO 2 // how much downscale original cam image for speed-up face detector?
#define SKIP_N_FRAMES 1 // how many webcam frames skip from face detector?
#define SMILE_CASCADE_FILEPATH "haarcascade_smile.xml" // trained haar descriptor for smile recognition
#define BORDER_SIZE 5 // the border size for calculate roi in videofram

// convert dlib rectangle to an opencv one
cv::Rect dlibRect2cvRect(dlib::rectangle, unsigned int, unsigned int);

// globals
// init or declare main scoped vars
//cv::VideoCapture cap(0); // prepare camera 0
//cv::Mat videoframe;	// store here video frame
//cv::Mat gray_videoframe; // store here video frame in gray-scale
//cv::Mat gray_videoframe_s; // store here video frame in gray-scale downscaled
////dlib::array2d<unsigned char> dlib_videoframe; // store here gray-scale video frame for dlib hog-based detector
//dlib::frontal_face_detector detector = dlib::get_frontal_face_detector(); // init HOG-based face detector
//std::vector<dlib::rectangle> dets; // vector for store faces bounding boxes in dlib format
//cv::CascadeClassifier smileCascade = cv::CascadeClassifier(SMILE_CASCADE_FILEPATH); // cascade classifier
//unsigned char count = 0; // the skip counter

extern "C"
{
	FACETRACKERLIB_API char* sayHello();
	FACETRACKERLIB_API void init();
}