#include "ChromaDLL.h"

cv::Mat frame;
cv::Mat maskFrame;
int count; // frame count

void writeFrames(char * path, cv::Mat image)
{
	std::stringstream imgname;
	imgname << path << count << ".jpg";
	cv::imwrite(imgname.str(), image);
}

extern "C"
{
	// MISC FUNCTIONALITY
	void updateCount()
	{
		count++;
	}

	void terminatePlugin()
	{
		count = 0;
		input::releaseCamera();
		segmentation::terminate();
	}
	
	// ============================================================
	// INPUT MODULE

	void initCamera()
	{		
		input::initCamera();
	}

	void takePhoto()
	{
		input::takePhoto();
	}

	void releaseCamera()
	{
		input::releaseCamera();
	}

	// ============================================================
	// SEGMENTATION MODULE

	void calibrate()
	{
		// calculate averaged frame
		frame = input::getPhoto();
		segmentation::getCalibrated(frame, frame);

		// save image
		writeFrames("img/calibrated", frame);
	}

	void calculateMask()
	{
		// calculate averaged frame
		segmentation::getMask(maskFrame, input::getPhoto());

		// save image
		writeFrames("img/mask", maskFrame);
	}

	void terminateSegmentation()
	{
		segmentation::terminate();
	}

}