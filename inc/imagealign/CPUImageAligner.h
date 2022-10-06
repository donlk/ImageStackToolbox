// Copyright (c) 2022 András Lehotay-Kéry

#ifndef CPU_IMAGE_ALIGNER
#define CPU_IMAGE_ALIGNER

#include "../detectorextractor/FastAKAZEDetectorExtractor.h"
#include "../detectorextractor/OpenCVAKAZEDetectorExtractor.h"
#include "../matcher/OpenCVFlannMatcher.h"
#include "ImageAligner.h"

class CPUImageAligner: public ImageAligner<FastAKAZEDetectorExtractor, OpenCVFlannMatcher>{
	public:
		CPUImageAligner();
		~CPUImageAligner();
};

#endif
