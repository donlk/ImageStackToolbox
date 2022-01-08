#ifndef OPENCV_BRUTE_FORCE_MATCHER
#define OPENCV_BRUTE_FORCE_MATCHER

#include "OpenCVMatcher.h"

class OpenCVBFMatcher: public OpenCVMatcher<cv::BFMatcher>{
	public:
		OpenCVBFMatcher(cv::NormTypes normType=cv::NormTypes::NORM_L2);
		virtual ~OpenCVBFMatcher();

	protected:
		cv::Ptr<cv::BFMatcher> getConcreteMatcher() override;

	private:
		cv::NormTypes normType;
};

#endif
