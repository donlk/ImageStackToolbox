#include <fast_akaze/fast_akaze/features2d_akaze2.hpp>

#include "../../inc/detectorextractor/FastAKAZEDetectorExtractor.h"

using namespace std;

FastAKAZEDetectorExtractor::FastAKAZEDetectorExtractor(){
	detectorExtractor = cv::AKAZE2::create(cv::AKAZE2::DESCRIPTOR_KAZE, 486, 3, 0.001f, 4, 4);
}

FastAKAZEDetectorExtractor::~FastAKAZEDetectorExtractor(){
	// NOOP
}

void FastAKAZEDetectorExtractor::detectAndCompute(
	cv::Mat img,
	std::vector<cv::KeyPoint>& outKeypoints,
	cv::Mat& outDescriptors
){
	cv::Mat imgGray;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	detectorExtractor->detectAndCompute(imgGray, cv::noArray(), outKeypoints, outDescriptors);
}
