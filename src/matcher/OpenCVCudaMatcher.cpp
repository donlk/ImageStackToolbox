// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/matcher/OpenCVCudaMatcher.h"

template<class MatcherType>
OpenCVCudaMatcher<MatcherType>::OpenCVCudaMatcher(): initialized(false){
	// NOOP
}

template<class MatcherType>
OpenCVCudaMatcher<MatcherType>::~OpenCVCudaMatcher(){
	// NOOP
}

template<class MatcherType>
void OpenCVCudaMatcher<MatcherType>::initialize(){
	matcher = getTypedMatcher();
	initialized = true;
}

template<class MatcherType>
std::vector<std::vector<cv::DMatch> > OpenCVCudaMatcher<MatcherType>::knnMatch(cv::Mat& descA, cv::Mat& descB){
	if(!initialized){
		initialize();
	}

	cv::cuda::GpuMat descAGpu, descBGpu;
	descAGpu.upload(descA);
	descBGpu.upload(descB);

	// Find two nearest matches
	// This returns the top two matches for each descriptor
	std::vector<std::vector<cv::DMatch>> matches;
	matcher->knnMatch(descAGpu, descBGpu, matches, 2);

	return matches;
}

