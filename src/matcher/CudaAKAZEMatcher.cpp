// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/matcher/CudaAKAZEMatcher.h"

CudaAKAZEMatcher::CudaAKAZEMatcher(){
	// NOOP
}

CudaAKAZEMatcher::~CudaAKAZEMatcher(){
	// NOOP
}

std::vector<std::vector<cv::DMatch> > CudaAKAZEMatcher::knnMatch(cv::Mat& descA, cv::Mat& descB){
	// Find two nearest matches
	// This returns the top two matches for each descriptor
	std::vector<std::vector<cv::DMatch>> matches;
	matcher.bfmatch(descA, descB, matches);

	return matches;
}

