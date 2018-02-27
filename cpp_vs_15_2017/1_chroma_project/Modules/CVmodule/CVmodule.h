#pragma once

#include <iostream>
#include "Input.h"
#include "Segmentation.h"
#include "NoiseReduction.h"
#include "Features.h"


class CVmodule
{
public:
	// PROPERTIES
	Input in;
	Segmentation segmentation;
	NoiseReduction noiseReduction;
	Features feature;

	double *centroid;
	double *normalizedCentroid;

	// METHODS
	CVmodule();
	void update();
	~CVmodule();
};

