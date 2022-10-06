// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/matcher/OpenCVBFMatcher.h"

OpenCVBFMatcher::OpenCVBFMatcher(cv::NormTypes normType):
	OpenCVMatcher<cv::BFMatcher>(0.8), normType(normType)
{
	// NOOP
}

OpenCVBFMatcher::~OpenCVBFMatcher(){
	// NOOP
}

cv::Ptr<cv::BFMatcher> OpenCVBFMatcher::getConcreteMatcher(){
	return new cv::BFMatcher(normType, false);
}
