#include "features.h"

namespace features
{
	cv::Moments moments;
}

void features::calculateMoments(cv::Mat inFrame)
{
	moments = cv::moments(inFrame);
}

double features::getCentroid_x()
{	
	// centroid will bee 0,0 when area is equal or less than 1
	if (moments.m00 <= 1)
	{
		return 0.0;
	}
	return moments.m10 / moments.m00;;
}

double features::getCentroid_y()
{
	// centroid will bee 0,0 when area is equal or less than 1
	if (moments.m00 <= 1)
	{
		return 0.0;
	}
	return moments.m01 / moments.m00;;
}
