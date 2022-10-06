// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/matcher/OpenCVCudaBFMatcher.h"

OpenCVCudaBFMatcher::OpenCVCudaBFMatcher(cv::NormTypes normType):
	OpenCVCudaMatcher<cv::cuda::DescriptorMatcher>(), normType(normType)
{
	// NOOP
}

OpenCVCudaBFMatcher::~OpenCVCudaBFMatcher(){
	// NOOP
}

cv::Ptr<cv::cuda::DescriptorMatcher> OpenCVCudaBFMatcher::getTypedMatcher(){
	return cv::cuda::DescriptorMatcher::createBFMatcher(normType);
}
