#include "Features.h"




Features::Features()
{
	centroid = (double*)malloc(2 * sizeof(double));
	normCentroid = (double*)malloc(2 * sizeof(double));
}

double *Features::calculateCentroid(cv::Mat inFrame)
{
	moments = cv::moments(inFrame);

	// centroid will bee 0,0 when area is equal or less than 1
	if (moments.m00 <= 1)
	{
		*centroid = 0;	*(centroid + 1) = 0;
		return centroid;
	}

	*centroid = moments.m10 / moments.m00;
	*(centroid + 1) = moments.m01 / moments.m00;
	return centroid;
}

double *Features::calculateNormCentroid(cv::Mat inFrame)
{
	moments = cv::moments(inFrame);

	// centroid will bee 0,0 when area is qeual or less than 1
	if (moments.m00 <= 1)
	{
		*normCentroid = 0;	*(normCentroid + 1) = 0;
		return normCentroid;
	}

	*normCentroid = moments.m10 / moments.m00;
	*normCentroid /= inFrame.cols;
	*(normCentroid + 1) = moments.m01 / moments.m00;
	*(normCentroid + 1) /= inFrame.rows;
	return normCentroid;
}

Features::~Features()
{
	//free(centroid);
}
