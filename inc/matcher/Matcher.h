#ifndef MATCHER
#define MATCHER

#include <opencv2/opencv.hpp>

#include <string>
#include <vector>

class Matcher{
	public:
		Matcher();
		virtual ~Matcher();

		virtual std::vector<std::vector<cv::DMatch> > knnMatch(cv::Mat& descA, cv::Mat& descB) = 0;

};

#endif
