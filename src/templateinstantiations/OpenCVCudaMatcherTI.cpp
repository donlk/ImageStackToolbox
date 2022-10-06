// Copyright (c) 2022 András Lehotay-Kéry

#include "../matcher/OpenCVCudaMatcher.cpp"

#include "../../inc/matcher/OpenCVCudaBFMatcher.h"

#include <opencv2/opencv.hpp>
#include <opencv2/cudafeatures2d.hpp>

template class OpenCVCudaMatcher<cv::cuda::DescriptorMatcher>;
