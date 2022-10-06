// Copyright (c) 2022 András Lehotay-Kéry

#ifndef OPENCV_MATCHER
#define OPENCV_MATCHER

#include "Matcher.h"

template<class MatcherType>
class OpenCVMatcher: public Matcher{
	/*static_assert(
		std::is_base_of<cv::DescriptorMatcher, MatcherType>::value,
		"MatcherType must inherit from cv::DescriptorMatcher!"
	);*/

	public:
		OpenCVMatcher(const float distanceRatio);
		virtual ~OpenCVMatcher();

		std::vector<std::vector<cv::DMatch> > knnMatch(cv::Mat& descA, cv::Mat& descB) override;

	protected:
		virtual cv::Ptr<MatcherType> getConcreteMatcher() = 0;

	private:
		void initialize();

	private:
		bool initialized;
		float distanceRatio;

		cv::Ptr<MatcherType> matcher;
};

#endif
