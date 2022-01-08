#ifndef MATCH_FILTER_UTILS
#define MATCH_FILTER_UTILS

#include <vector>
#include <opencv2/opencv.hpp>

class MatchUtils{
	public:
		static void computeFundamentalMat(
			const std::vector<cv::Point2f>& queryPts,
			const std::vector<cv::Point2f>& trainPts,
			const float error,
			cv::Mat& outFMat,
			cv::Mat& outStatusMat
		);

		static void computeHomographyMat(
			const std::vector<cv::Point2f>& queryPts,
			const std::vector<cv::Point2f>& trainPts,
			const float error,
			cv::Mat& outHMat,
			cv::Mat& outStatusMat
		);
};


#endif
