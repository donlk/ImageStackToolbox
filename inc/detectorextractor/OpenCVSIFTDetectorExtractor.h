// Copyright (c) 2022 András Lehotay-Kéry

#ifndef OPENCV_SIFT_DETECTOR_EXTRACTOR
#define OPENCV_SIFT_DETECTOR_EXTRACTOR

#include "DetectorExtractorBase.h"

class OpenCVSIFTDetectorExtractor: public DetectorExtractorBase{
	public:
		OpenCVSIFTDetectorExtractor();
		~OpenCVSIFTDetectorExtractor();

		void detectAndCompute(
			cv::Mat img,
			std::vector<cv::KeyPoint>& outKeypoints,
			cv::Mat& outDescriptors
		) override;
	private:
		cv::Ptr<cv::Feature2D> detectorExtractor;
};

#endif // OPENCV_SIFT_DETECTOR_EXTRACTOR
