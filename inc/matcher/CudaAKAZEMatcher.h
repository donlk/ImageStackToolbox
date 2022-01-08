#ifndef CUDA_AKAZE_MATCHER
#define CUDA_AKAZE_MATCHER

#include "Matcher.h"

#include <cuda_akaze/src/lib/AKAZE.h>

class CudaAKAZEMatcher: public Matcher{
	public:
		CudaAKAZEMatcher();
		virtual ~CudaAKAZEMatcher();

		std::vector<std::vector<cv::DMatch> > knnMatch(cv::Mat& descA, cv::Mat& descB) override;

	private:
		libAKAZECU::Matcher matcher;
};

#endif
