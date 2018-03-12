#include "ChromaDLL.h"

cv::Mat frame;
cv::Mat maskFrame;
cv::Mat noiselessFrame;

#ifdef rjlvmj_DEBUG_MODE
#include <fstream>
std::ofstream logFile("img/000aaalogfile.txt");
int count; // frame count
#endif // rjlvmj_DEBUG_MODE

void writeFrames(char * path, cv::Mat image)
{
#ifdef rjlvmj_DEBUG_MODE
	std::stringstream imgname;
	imgname << path << count << ".jpg";
	cv::imwrite(imgname.str(), image);
#endif // rjlvmj_DEBUG_MODE	
}

extern "C"
{
	// MISC FUNCTIONALITY
	void updateCount()
	{
#ifdef rjlvmj_DEBUG_MODE
		logFile << "FRAME" << count << ":\n";
		logFile << "\tframe.cols: " << frame.cols;
		logFile << "\tframe.rows: " << frame.rows << std::endl;
		logFile << "\tx: " << getCentroid_x();
		logFile << "\ty: " << getCentroid_y() << std::endl;
		logFile << "\txn: " << getNormCentroid_x();
		logFile << "\tyn: " << getNormCentroid_y() << std::endl;
		count++;
#endif // rjlvmj_DEBUG_MODE
	}

	void terminatePlugin()
	{
#ifdef rjlvmj_DEBUG_MODE
		count = 0;
#endif // rjlvmj_DEBUG_MODE
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

#ifdef rjlvmj_DEBUG_MODE
		// save image
		writeFrames("img/calibrated", frame);
#endif // rjlvmj_DEBUG_MODE		
	}

	void calculateMask()
	{
		// calculate averaged frame
		segmentation::getMask(maskFrame, input::getPhoto());
		cv::cvtColor(maskFrame, maskFrame, cv::COLOR_BGR2GRAY);

#ifdef rjlvmj_DEBUG_MODE
		// save image
		writeFrames("img/mask", maskFrame);
#endif // rjlvmj_DEBUG_MODE	
	}

	void terminateSegmentation()
	{
		segmentation::terminate();
	}

	// ============================================================
	// NOISE REDUCTION MODULE

	void reduceNoise()
	{
		noiseReduction::process(noiselessFrame, maskFrame, 5);

#ifdef rjlvmj_DEBUG_MODE
		// save image
		writeFrames("img/noiseless", noiselessFrame);
#endif // rjlvmj_DEBUG_MODE	
	}

	// ============================================================
	// FEATURES MODULE

	void calculateCentroid()
	{
		features::calculateMoments(noiselessFrame);

#ifdef rjlvmj_DEBUG_MODE
		double x = features::getCentroid_x();
		double y = features::getCentroid_y();
		cv::Mat centroidFrame;
		centroidFrame = input::getPhoto();
		cv::circle(centroidFrame, cv::Point(x, y), 5, cv::Scalar(255.0, 0.0, 0.0, 1.0), 20);
		writeFrames("img/zentroid", centroidFrame);
#endif // rjlvmj_DEBUG_MODE	
	}
	double getCentroid_x()
	{
		return features::getCentroid_x();
	}

	double getCentroid_y()
	{
		return features::getCentroid_y();
	}
	double getNormCentroid_x()
	{
		double w = frame.cols;
		return getCentroid_x() / w;
	}
	double getNormCentroid_y()
	{
		return getCentroid_y() / (double)frame.rows;
	}
}