#include "face_tracker.h"

// init or declare main scoped vars

cv::VideoCapture cap;
cv::Mat videoframe;	// store here video frame
cv::Mat gray_videoframe; // store here video frame in gray-scale
cv::Mat gray_videoframe_s; // store here video frame in gray-scale downscaled
//dlib::array2d<unsigned char> dlib_videoframe; // store here gray-scale video frame for dlib hog-based detector
dlib::frontal_face_detector detector = dlib::get_frontal_face_detector(); // init HOG-based face detector
std::vector<dlib::rectangle> dets; // vector for store faces bounding boxes in dlib format
cv::CascadeClassifier smileCascade = cv::CascadeClassifier(SMILE_CASCADE_FILEPATH); // cascade classifier
float ft_x = 0;
float ft_y = 0;
bool ft_isSmiling = false;
unsigned char count = 0;
																			//unsigned char count = 0; // the skip counter
#ifdef FT_WRITE_DEBUG_FILE
#include <fstream>
std::fstream logFile;
#endif // FT_WRITE_DEBUG_FILE

void initCam()
{
	cap = cv::VideoCapture(0);
	// check if camera is available
	if (!cap.isOpened())
	{
		std::cout << "Sorry, can't use webcam" << std::endl;
		return;
	}
}

void releaseCam()
{
	cap.release();
	count = 0;
}

cv::Mat getCamFrame()
{
	cv::Mat frame;
	cap >> frame;
	return frame;
}

FACETRACKERLIB_API void ftInit()
{
#ifdef FT_WRITE_DEBUG_FILE
	logFile.open("faceTrackerDebugOut/0aLogFile.txt", std::fstream::out);
	logFile << "ftInit() is correct\n";
#endif // FT_WRITE_DEBUG_FILE
	initCam();	
}

FACETRACKERLIB_API void ftTrack()
{
#ifdef FT_WRITE_DEBUG_FILE
	logFile << "frame " << (unsigned int)count << ": \n";
#endif // FT_WRITE_DEBUG_FILE

	videoframe = getCamFrame();
	cv::flip(videoframe, videoframe, 1);
	cv::cvtColor(videoframe, gray_videoframe, cv::COLOR_BGR2GRAY);


	if (count % SKIP_N_FRAMES == 0)
	{
		// scale image for speed-up face detector
		cv::resize(gray_videoframe, gray_videoframe_s, cv::Size(), 1.0 / DOWNSAMPLE_RATIO, 1.0 / DOWNSAMPLE_RATIO);

		// convert frame to dlib format, no memory is copied.
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

		ft_x = faceRect.x + (float)(faceRect.width / 2.0f); // normalized x
		ft_x = ft_x / (float)videoframe.cols;
		ft_y = faceRect.y + (float)(faceRect.height / 2.0f); // normalized y
		ft_y = ft_y / (float)videoframe.rows;

#ifdef FT_WRITE_DEBUG_FILE
		logFile << "\tW: " << videoframe.cols << " H: " << videoframe.rows << std::endl;
		logFile << "\tFACE: <" << faceRect.x << ", " << faceRect.y << ">\n";
		logFile << "\tFACEn: <" << (float)faceRect.x / videoframe.cols << ", " << (float)faceRect.y / videoframe.rows << ">\n";
		logFile << "\tCENTR: <" << faceRect.x + (faceRect.width/2) << ", " << faceRect.y + (faceRect.height/2) << ">\n";
		logFile << "\tCENTRn: <" << ft_x << ", " << ft_y << ">\n";
		cv::rectangle(videoframe, faceRect, cv::Scalar(255, 0, 0), 5);
		cv::circle(videoframe,
					cv::Point(faceRect.x + faceRect.width/2, faceRect.y + faceRect.width/2),
					3, cv::Scalar(0, 0, 255), 5);
#endif // FT_WRITE_DEBUG_FILE
		

		// detect smile
		std::vector<cv::Rect> smilesRect;
		smileCascade.detectMultiScale(faceROI, smilesRect, 1.7, 22, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(25, 25));
		//std::cout << "Number of smiles detected: " << smilesRect.size() << std::endl;

		// show smile bounding box
		if (smilesRect.size() > 0)
		{
			ft_isSmiling = true;
			smilesRect[0].x += faceRect.x;
			smilesRect[0].y += faceRect.y;
#ifdef FT_WRITE_DEBUG_FILE
			logFile << "\tis smiling\n";
			cv::rectangle(videoframe, smilesRect[0], cv::Scalar(0, 255, 0), 5);
#endif // FT_WRITE_DEBUG_FILE			
		}
		else
		{
			ft_isSmiling = false;
		}

	}
	// show videoframe
#ifdef FT_WRITE_DEBUG_FILE
	writeFrames("faceTrackerDebugOut/frame", videoframe, count);
#endif // FT_WRITE_DEBUG_FILE	
	count++;
	return;
}

FACETRACKERLIB_API void ftTerminate()
{
	releaseCam();
#ifdef FT_WRITE_DEBUG_FILE
	logFile.close();
	logFile << "ftTerminate() is correct\n";
#endif
}

FACETRACKERLIB_API double ftGetX()
{
	return ft_x;	
}

FACETRACKERLIB_API double ftGetY()
{
	return ft_y;
}

FACETRACKERLIB_API bool ftIsSmiling()
{
	return ft_isSmiling;
}

cv::Rect dlibRect2cvRect(dlib::rectangle dlib_rect, unsigned int w, unsigned int h)
{
	static cv::Rect rect;

	// extract dlib rectangle data
	long left = dlib_rect.left();
	long width = dlib_rect.width();
	long top = dlib_rect.top();
	long height = dlib_rect.height();

	// rect.x > 0 && rect.x + width < w
	rect.x = left <= BORDER_SIZE ? 0 : left + width >= w - BORDER_SIZE ? (w - width) * DOWNSAMPLE_RATIO : left * DOWNSAMPLE_RATIO;
	rect.y = top <= BORDER_SIZE ? 0 : top + height >= h - BORDER_SIZE ? (h - height) * DOWNSAMPLE_RATIO : top * DOWNSAMPLE_RATIO;
	rect.width = (unsigned int)width * DOWNSAMPLE_RATIO;
	rect.height = (unsigned int)height * DOWNSAMPLE_RATIO;

	return rect;
}

void writeFrames(std::string path, cv::Mat image, unsigned int count)
{
	std::stringstream imgname;
	imgname << path << (unsigned int)count << ".jpg";
	cv::imwrite(imgname.str(), image);
}