// Copyright (c) 2022 András Lehotay-Kéry

#ifndef CUDA_AKAZE_DETECTOR_EXTRACTOR
#define CUDA_AKAZE_DETECTOR_EXTRACTOR

#include "DetectorExtractorBase.h"

#include <cuda_akaze/src/lib/AKAZEConfig.h>
#include <cuda_akaze/src/lib/AKAZE.h>

class CudaAKAZEDetectorExtractor: public DetectorExtractorBase{
	public:
		CudaAKAZEDetectorExtractor();
		~CudaAKAZEDetectorExtractor();

		void detectAndCompute(
			cv::Mat img,
			std::vector<cv::KeyPoint>& outKeypoints,
			cv::Mat& outDescriptors
		) override;
	private:
		AKAZEOptions options;
};

#endif
