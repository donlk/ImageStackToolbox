#ifndef OPENCV_FLANN_MATCHER
#define OPENCV_FLANN_MATCHER

#include "OpenCVMatcher.h"

class OpenCVFlannMatcher: public OpenCVMatcher<cv::FlannBasedMatcher>{
	public:
		OpenCVFlannMatcher();
		virtual ~OpenCVFlannMatcher();
	protected:
		cv::Ptr<cv::FlannBasedMatcher> getConcreteMatcher() override;
};

#endif
