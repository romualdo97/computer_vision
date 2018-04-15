#pragma once
// include opencv
#include <opencv2\opencv.hpp>
// include dlib
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\opencv\cv_image.h>
// include standards
#include <iostream>
#include <sstream>
#include <string>
// helper functions
#include "input.h"

#ifdef FACETRACKERLIB_EXPORTS
#define FACETRACKERLIB_API __declspec(dllexport)
#else
#define FACETRACKERLIB_API __declspec(dllimport)
#endif // FACETRACKERLIB_EXPORTS

#define DOWNSAMPLE_RATIO 2 // how much downscale original cam image for speed-up face detector?
#define SKIP_N_FRAMES 1 // how many webcam frames skip from face detector?
#define SMILE_CASCADE_FILEPATH "haarcascade_smile.xml" // trained haar descriptor for smile recognition
#define BORDER_SIZE 5 // the border size for calculate roi in videofram
#define FT_WRITE_DEBUG_FILE

// convert dlib rectangle to an opencv one
cv::Rect dlibRect2cvRect(dlib::rectangle, unsigned int, unsigned int);
void writeFrames(std::string, cv::Mat image, unsigned int count);

extern "C"
{
	// basic functions
	FACETRACKERLIB_API void ftInit();
	FACETRACKERLIB_API void ftTrack();
	FACETRACKERLIB_API void ftTerminate();

	// info functions
	FACETRACKERLIB_API double ftGetX();
	FACETRACKERLIB_API double ftGetY();
	FACETRACKERLIB_API bool ftIsSmiling();
}