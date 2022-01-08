#include "../../inc/util/MatchUtils.h"

using namespace std;

void MatchUtils::computeFundamentalMat(
	const std::vector<cv::Point2f>& queryPts,
	const std::vector<cv::Point2f>& trainPts,
	const float error,
	cv::Mat& outFMat,
	cv::Mat& outStatusMat
){
	size_t pointNum = queryPts.size();
	outStatusMat = cv::Mat::zeros(pointNum, 1, CV_8UC1);

	if (pointNum > 8) {
		outFMat = cv::findFundamentalMat(queryPts, trainPts, cv::FM_RANSAC, error, 0.99, outStatusMat);
	}else{
		cerr << "[MatchUtils][computeFundamentalMat] ERROR: Insufficient points provided." << endl;
	}
}

void MatchUtils::computeHomographyMat(
	const std::vector<cv::Point2f>& queryPts,
	const std::vector<cv::Point2f>& trainPts,
	const float error,
	cv::Mat& outHMat,
	cv::Mat& outStatusMat
){
	size_t pointNum = queryPts.size();
	outStatusMat = cv::Mat::zeros(pointNum, 1, CV_8UC1);

	if (pointNum > 8) {
		outHMat = cv::findHomography(queryPts, trainPts, cv::RANSAC, error, outStatusMat);
	}else{
		cerr << "[MatchUtils][computeHomographyMat] ERROR: Insufficient points provided." << endl;
	}
}
