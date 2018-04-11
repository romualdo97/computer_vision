#include "CVmodule.h"



CVmodule::CVmodule()
{
	std::cout << "\n\nInitializing CV module" << std::endl;
	//centroid = (double*)malloc(2 * sizeof(double));
}

bool CVmodule::update()
{
	// get input
	cv::Mat inputFrame = in.getFrame_bw();
	//cv::imshow("camera", inputFrame);
	if (cv::waitKey(30) == 'q')
	{
		return false;
	}
	return true;
	//// calculate mask
	//cv::Mat mask;
	//segmentation.process(mask, inputFrame);

	//// reduce noise
	//cv::Mat noiseless;
	//noiseReduction.process(noiseless, mask, 3);	

	//// calculate centroid
	//centroid = feature.calculateCentroid(noiseless);
	//normalizedCentroid = feature.calculateNormCentroid(noiseless);

#ifdef rjlvmj_DEBUG_MODE

	//// show mask before noise reduction
	//cv::imshow("No eroded image", mask);

	//// show mask after noise reduction
	//cv::imshow("eroded image", noiseless);

	//// show camera image and centroid
	////std::cout << "x: " << *c << std::endl;
	//cv::circle(inputFrame, cv::Point((int)*centroid, (int)*(centroid + 1)), 5, cv::Scalar(255.0, 0.0, 0.0, 1.0), 20);
	
	cv::imshow("camera", inputFrame);

#endif // rjlvmj_DEBUG_MODE

	
	
}

CVmodule::~CVmodule()
{
	//free(centroid);
}
