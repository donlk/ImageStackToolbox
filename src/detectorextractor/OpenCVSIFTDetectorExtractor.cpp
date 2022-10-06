// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/detectorextractor/OpenCVSIFTDetectorExtractor.h"

#include <opencv2/features2d/features2d.hpp>

using namespace std;

OpenCVSIFTDetectorExtractor::OpenCVSIFTDetectorExtractor(){
	detectorExtractor = cv::SIFT::create(0, 3, 0.004, 10, 1.6);
}

OpenCVSIFTDetectorExtractor::~OpenCVSIFTDetectorExtractor(){
	// NOOP
}

void OpenCVSIFTDetectorExtractor::detectAndCompute(
	cv::Mat img,
	std::vector<cv::KeyPoint>& outKeypoints,
	cv::Mat& outDescriptors
){
	cv::Mat imgGray;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	detectorExtractor->detectAndCompute(imgGray, cv::noArray(), outKeypoints, outDescriptors);
}
