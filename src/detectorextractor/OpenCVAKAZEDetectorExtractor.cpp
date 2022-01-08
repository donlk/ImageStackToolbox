#include <opencv2/features2d.hpp>
#include "../../inc/detectorextractor/OpenCVAKAZEDetectorExtractor.h"

using namespace std;

OpenCVAKAZEDetectorExtractor::OpenCVAKAZEDetectorExtractor(){
	detectorExtractor = cv::AKAZE::create(cv::AKAZE::DESCRIPTOR_KAZE, 486, 3, 0.0001f, 4, 4);
}

OpenCVAKAZEDetectorExtractor::~OpenCVAKAZEDetectorExtractor(){
	// NOOP
}

void OpenCVAKAZEDetectorExtractor::detectAndCompute(
	cv::Mat img,
	std::vector<cv::KeyPoint>& outKeypoints,
	cv::Mat& outDescriptors
){
	cv::Mat imgGray;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	detectorExtractor->detectAndCompute(imgGray, cv::noArray(), outKeypoints, outDescriptors);
}
