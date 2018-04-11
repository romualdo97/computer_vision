// include opencv
#include <opencv2\opencv.hpp>
// include dlib
#include <dlib\image_processing\frontal_face_detector.h>
#include <dlib\opencv\cv_image.h>
// include standards
#include <iostream>

#define DOWNSAMPLE_RATIO 2 // how much downscale original cam image for speed-up face detector?
#define SKIP_N_FRAMES 1 // how many webcam frames skip from face detector?
#define SMILE_CASCADE_FILEPATH "haarcascade_smile.xml"
// convert dlib rectangle to an opencv one
cv::Rect dlibRect2cvRect(dlib::rectangle, unsigned int, unsigned int);

int main(void)
{
	// init or declare main scoped vars
	cv::VideoCapture cap(0); // prepare camera 0
	cv::Mat videoframe;	// store here video frame
	cv::Mat gray_videoframe; // store here video frame in gray-scale
	cv::Mat gray_videoframe_s; // store here video frame in gray-scale downscaled
	//dlib::array2d<unsigned char> dlib_videoframe; // store here gray-scale video frame for dlib hog-based detector
	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector(); // init HOG-based face detector
	std::vector<dlib::rectangle> dets; // vector for store faces bounding boxes in dlib format
	cv::CascadeClassifier smileCascade = cv::CascadeClassifier(SMILE_CASCADE_FILEPATH); // cascade classifier
	unsigned char count = 0; // the skip counter

	// check if camera is available
	if (!cap.isOpened())
	{
		std::cout << "Sorry, can't use webcam" << std::endl;
		return false;
	}

	// windows loop
	while (true)
	{	
		// capture videoframe
		cap >> videoframe;
		cv::flip(videoframe, videoframe, 1);
		cv::cvtColor(videoframe, gray_videoframe, cv::COLOR_BGR2GRAY);
		

		if (count % SKIP_N_FRAMES == 0)
		{
			// scale image for speed-up face detector
			cv::resize(gray_videoframe, gray_videoframe_s, cv::Size(), 1.0 / DOWNSAMPLE_RATIO, 1.0 / DOWNSAMPLE_RATIO);

			// convert frame to dlib format, no memory is copied.
			//dlib::assign_image(dlib_videoframe, dlib::cv_image<unsigned char>(gray_videoframe));
			dlib::cv_image<unsigned char> dlib_videoframe(gray_videoframe_s);

			// detect face
			dets = detector(dlib_videoframe);
			//std::cout << "Number of faces detected: " << dets.size() << std::endl;
		}
				
		// draw face bounding box
		if (dets.size() > 0)
		{
			cv::Rect faceRect = dlibRect2cvRect(dets[0], gray_videoframe_s.cols, gray_videoframe_s.rows);
			cv::Mat faceROI = gray_videoframe(faceRect);
			cv::rectangle(videoframe, faceRect, cv::Scalar(255, 0, 0), 5);
			cv::imshow("faceroi", faceROI);
			std::vector<cv::Rect> smilesRect;

			// detect smile
			smileCascade.detectMultiScale(faceROI, smilesRect, 1.7, 22, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(25, 25));
			std::cout << "Number of smiles detected: " << smilesRect.size() << std::endl;

			// show smile bounding box
			if (smilesRect.size() > 0)
			{
				smilesRect[0].x += faceRect.x;
				smilesRect[0].y += faceRect.y;
				cv::rectangle(videoframe, smilesRect[0], cv::Scalar(0, 255, 0), 5);
			}
		}
		// show videoframe
		cv::imshow("Frame", videoframe);
		//std::cout << (unsigned int)count << std::endl;
		count++;
		if (cv::waitKey(30) == 'q')
		{
			break;
		}
	}
	return 0;
}

cv::Rect dlibRect2cvRect(dlib::rectangle dlib_rect, unsigned int w, unsigned int h)
{
	static cv::Rect rect;
	long left = dlib_rect.left();
	long width = dlib_rect.width();
	long top = dlib_rect.top();
	long height = dlib_rect.height();
	// rect.x > 0 && rect.x + width < w
	rect.x =  left <= 0 ? 0 : left + width >= w ? (w - left) * DOWNSAMPLE_RATIO : left * DOWNSAMPLE_RATIO;
	rect.y = top <= 0 ? 0 : top + height >= h ? (h - top) * DOWNSAMPLE_RATIO : top * DOWNSAMPLE_RATIO;
	rect.width = (unsigned int)  width * DOWNSAMPLE_RATIO;
	rect.height = (unsigned int) height * DOWNSAMPLE_RATIO;
	return rect;
}

// REFS:
// How to convert mat to array2d<rgb_pixel>?
//	- https://stackoverflow.com/questions/29118317/how-to-convert-mat-to-array2drgb-pixel/40687888
// Speeding up Dlib’s Facial Landmark Detector
//	- https://www.learnopencv.com/speeding-up-dlib-facial-landmark-detector/
// long Vs. int C/C++ - What's The Point?
//	- https://stackoverflow.com/questions/7456902/long-vs-int-c-c-whats-the-point/7456928
// Realtime smile detection in Python OpenCV
//	- http://pushbuttons.io/blog/2015/4/27/smile-detection-in-python-opencv