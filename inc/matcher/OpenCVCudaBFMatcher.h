// Copyright (c) 2022 András Lehotay-Kéry

#ifndef OPENCV_CUDA_BRUTE_FORCE_MATCHER
#define OPENCV_CUDA_BRUTE_FORCE_MATCHER

#include "OpenCVCudaMatcher.h"

#include <opencv2/opencv.hpp>
#include <opencv2/cudafeatures2d.hpp>

class OpenCVCudaBFMatcher: public OpenCVCudaMatcher<cv::cuda::DescriptorMatcher>{
	public:
		OpenCVCudaBFMatcher(cv::NormTypes normType=cv::NormTypes::NORM_L2);
		virtual ~OpenCVCudaBFMatcher();

	protected:
		cv::Ptr<cv::cuda::DescriptorMatcher> getTypedMatcher() override;

	private:
		cv::NormTypes normType;
};

#endif
