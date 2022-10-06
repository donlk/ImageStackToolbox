// Copyright (c) 2022 András Lehotay-Kéry

#ifndef FAST_AKAZE_DETECTOR_EXTRACTOR
#define FAST_AKAZE_DETECTOR_EXTRACTOR

#include "DetectorExtractorBase.h"

class FastAKAZEDetectorExtractor: public DetectorExtractorBase{
	public:
		FastAKAZEDetectorExtractor();
		~FastAKAZEDetectorExtractor();

		void detectAndCompute(
			cv::Mat img,
			std::vector<cv::KeyPoint>& outKeypoints,
			cv::Mat& outDescriptors
		) override;
	private:
		cv::Ptr<cv::Feature2D> detectorExtractor;
};

#endif
