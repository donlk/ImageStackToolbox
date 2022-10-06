// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/matcher/OpenCVFlannMatcher.h"

OpenCVFlannMatcher::OpenCVFlannMatcher(): OpenCVMatcher<cv::FlannBasedMatcher>(0.8){
	// NOOP
}

OpenCVFlannMatcher::~OpenCVFlannMatcher(){
	// NOOP
}

cv::Ptr<cv::FlannBasedMatcher> OpenCVFlannMatcher::getConcreteMatcher(){
	return new cv::FlannBasedMatcher();
}
