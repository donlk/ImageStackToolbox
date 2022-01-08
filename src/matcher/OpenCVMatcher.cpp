#include "../../inc/matcher/OpenCVMatcher.h"

template<class MatcherType>
OpenCVMatcher<MatcherType>::OpenCVMatcher(const float distanceRatio):
	initialized(false), distanceRatio(distanceRatio)
{
	// NOOP
}

template<class MatcherType>
OpenCVMatcher<MatcherType>::~OpenCVMatcher(){
	// NOOP
}

template<class MatcherType>
void OpenCVMatcher<MatcherType>::initialize(){
	matcher = getConcreteMatcher();
	initialized = true;
}

template<class MatcherType>
std::vector<std::vector<cv::DMatch> > OpenCVMatcher<MatcherType>::knnMatch(cv::Mat& descA, cv::Mat& descB){
	if(!initialized){
		initialize();
	}

	// Find two nearest matches
	// This returns the top two matches for each descriptor
	std::vector<std::vector<cv::DMatch>> matches;
	matcher->knnMatch(descA, descB, matches, 2);

	return matches;
}

