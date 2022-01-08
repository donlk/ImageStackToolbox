#include "../matcher/OpenCVMatcher.cpp"

#include "../../inc/matcher/OpenCVBFMatcher.h"
#include "../../inc/matcher/OpenCVCudaBFMatcher.h"
#include "../../inc/matcher/OpenCVFlannMatcher.h"

#include <opencv2/opencv.hpp>
#include <opencv2/cudafeatures2d.hpp>

template class OpenCVMatcher<cv::FlannBasedMatcher>;
template class OpenCVMatcher<cv::BFMatcher>;
template class OpenCVMatcher<cv::cuda::DescriptorMatcher>;
