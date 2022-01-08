#ifndef DETECTOR_EXTRACTOR_BASE
#define DETECTOR_EXTRACTOR_BASE

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class DetectorExtractorBase{
	public:
		DetectorExtractorBase();
		virtual ~DetectorExtractorBase();

		virtual void detectAndCompute(
			cv::Mat img,
			std::vector<cv::KeyPoint>& outKeypoints,
			cv::Mat& outDescriptors
		) = 0;

};

#endif
