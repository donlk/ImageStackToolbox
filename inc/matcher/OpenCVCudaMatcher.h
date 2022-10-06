// Copyright (c) 2022 András Lehotay-Kéry

#ifndef OPENCV_CUDA_MATCHER
#define OPENCV_CUDA_MATCHER

#include "Matcher.h"

#include <opencv2/cudafeatures2d.hpp>

template<class MatcherType>
class OpenCVCudaMatcher: public Matcher{
	static_assert(
		std::is_base_of<cv::cuda::DescriptorMatcher, MatcherType>::value,
		"MatcherType must inherit from cv::cuda::DescriptorMatcher!"
	);

	public:
		OpenCVCudaMatcher();
		virtual ~OpenCVCudaMatcher();

		std::vector<std::vector<cv::DMatch> > knnMatch(cv::Mat& descA, cv::Mat& descB) override;

	protected:
		virtual cv::Ptr<MatcherType> getTypedMatcher() = 0;

	private:
		void initialize();

	private:
		bool initialized;

		cv::Ptr<MatcherType> matcher;
};

#endif
