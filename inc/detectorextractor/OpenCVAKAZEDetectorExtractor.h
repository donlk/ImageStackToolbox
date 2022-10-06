// Copyright (c) 2022 András Lehotay-Kéry

#ifndef OPENCV_AKAZE_DETECTOR_EXTRACTOR
#define OPENCV_AKAZE_DETECTOR_EXTRACTOR

#include "DetectorExtractorBase.h"

class OpenCVAKAZEDetectorExtractor: public DetectorExtractorBase{
	public:
		OpenCVAKAZEDetectorExtractor();
		~OpenCVAKAZEDetectorExtractor();

		void detectAndCompute(
			cv::Mat img,
			std::vector<cv::KeyPoint>& outKeypoints,
			cv::Mat& outDescriptors
		) override;
	private:
		cv::Ptr<cv::Feature2D> detectorExtractor;
};

#endif
