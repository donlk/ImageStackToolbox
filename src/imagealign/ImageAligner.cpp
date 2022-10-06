// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/imagealign/ImageAligner.h"

#include "../../inc/image/Image.h"
#include "../../inc/exceptions/InsufficientDataException.hpp"
#include "../../inc/detectorextractor/FastAKAZEDetectorExtractor.h"
#include "../../inc/detectorextractor/OpenCVAKAZEDetectorExtractor.h"
#include "../../inc/detectorextractor/CudaAKAZEDetectorExtractor.h"
#include "../../inc/detectorextractor/OpenCVSIFTDetectorExtractor.h"
#include "../../inc/matcher/OpenCVBFMatcher.h"
#include "../../inc/matcher/OpenCVCudaBFMatcher.h"
#include "../../inc/matcher/OpenCVFlannMatcher.h"
#include "../../inc/matcher/CudaAKAZEMatcher.h"
#include "../../inc/util/MatchUtils.h"

#include <string>
#include <cmath>
#include <iostream>

using namespace std;

template<class DetectorExtractorType, class MatcherType>
ImageAligner<DetectorExtractorType, MatcherType>::ImageAligner(){
	detectorExtractor = make_shared<DetectorExtractorType>();
	matcher = make_shared<MatcherType>();
}

template<class DetectorExtractorType, class MatcherType>
ImageAligner<DetectorExtractorType, MatcherType>::~ImageAligner(){
	// NOOP
}

template<class DetectorExtractorType, class MatcherType>
std::vector<cv::Mat> ImageAligner<DetectorExtractorType, MatcherType>::alignImages(
	std::vector<std::shared_ptr<Image> > inImgs
){
	vector<cv::Mat> outImages;

	// We assume that image 0 is the "base" image and align everything to it
	outImages.push_back(inImgs[0]->getMat());

	timer.start();

	vector<cv::KeyPoint> keypointsBase;
	cv::Mat descriptorsBase;
	detectorExtractor->detectAndCompute(inImgs[0]->getMat(), keypointsBase, descriptorsBase);
	cout
		<< "Features base image: "
		<< keypointsBase.size() <<
		", TIME: "
		<< timer.getElapsedMillis().count()
		<< "ms"
	<< endl;

	for(size_t i = 1; i < inImgs.size(); ++i){
		cout << "Aligning image [" << i << "/" << inImgs.size() << "]" << endl;

		vector<cv::KeyPoint> keypoints;
		cv::Mat descriptors;
		timer.start();
		detectorExtractor->detectAndCompute(inImgs[i]->getMat(), keypoints, descriptors);
		cout
			<< "Features image: "
			<< keypoints.size() <<
			", TIME: "
			<< timer.getElapsedMillis().count()
			<< "ms"
		<< endl;

		timer.start();
		std::vector<std::vector<cv::DMatch> > knnMatches = matcher->knnMatch(
			descriptors,
			descriptorsBase
		);
		cout << "Matching TIME: " << timer.getElapsedMillis().count() << "ms" << endl;

		vector<cv::KeyPoint> filteredKeypoints;
		std::vector<cv::Point2f> filteredPoints;
		std::vector<cv::Point2f> filteredPointsBase;
		std::vector<cv::DMatch> filteredMatches;
		for(size_t i = 0; i < knnMatches.size(); ++i){
			cv::DMatch match1 = knnMatches[i][0];
			cv::DMatch match2 = knnMatches[i][1];
			if(
				knnMatches[i].size() == 1
				|| match1.distance < MATCH_DISTANCE_RATIO_THRESHOLD * match2.distance
			){
				filteredKeypoints.push_back(keypoints[match1.queryIdx]);
				filteredPoints.push_back(keypoints[match1.queryIdx].pt);
				filteredPointsBase.push_back(keypointsBase[match1.trainIdx].pt);
				filteredMatches.push_back(match1);
			}
		}

		cv::Mat fMat, fStatusMat;
		MatchUtils::computeFundamentalMat(
			filteredPoints,
			filteredPointsBase,
			INLIER_ERROR_THRESHOLD,
			fMat,
			fStatusMat
		);

		std::vector<cv::KeyPoint> goodKeyPoints;
		std::vector<cv::Point2f> goodPoints;
		std::vector<cv::Point2f> goodPointsBase;
		std::vector<cv::DMatch> goodMatches;
		for (int i = 0; i < filteredPoints.size(); i++){
			if (fStatusMat.at<unsigned char>(i) == 1){
				goodKeyPoints.push_back(filteredKeypoints[i]);
				goodPoints.push_back(filteredPoints[i]);
				goodPointsBase.push_back(filteredPointsBase[i]);
				goodMatches.push_back(filteredMatches[i]);
			}
		}

		cout << "goodPoints: " << goodPoints.size() << endl;
		cout << "goodPointsBase: " << goodPointsBase.size() << endl;
		cout << "goodMatches for image: [" << inImgs[i]->getName() << ", " << goodMatches.size() << "]" << endl;

		/*cv::Mat matchDisplay;
		cv::drawMatches(
			inImgs[i]->getMat(),
			keypoints,
			inImgs[0]->getMat(),
			keypointsBase,
			goodMatches,
			matchDisplay,
			cv::Scalar::all(-1),
			cv::Scalar(255,0,0)
		);
		cv::namedWindow("good matches", cv::WINDOW_NORMAL);
		cv::resizeWindow("good matches", 1280, 720);
		cv::imshow("good matches", matchDisplay);
		cv::waitKey(300);*/

		cv::Mat hMat, hStatusMat;
		MatchUtils::computeHomographyMat(
			goodPoints,
			goodPointsBase,
			INLIER_ERROR_THRESHOLD,
			hMat,
			hStatusMat
		);

		if(hMat.empty()){
			cout << "Homography matrix is empty for image: " << i << endl;
			continue;
		}

		cv::Mat newImg;
		cv::warpPerspective(
			inImgs[i]->getMat(),
			newImg,
			hMat,
			cv::Size(inImgs[i]->getMat().cols, inImgs[i]->getMat().rows),
			cv::INTER_LINEAR,
			cv::BORDER_CONSTANT
		);
		outImages.push_back(newImg);
	}
	return outImages;
}

std::shared_ptr<ImageAlignerBase> createImageAlignerFromParams(
	const std::string& detectorExtractorType,
	const std::string& matcherType
){
	if(detectorExtractorType == "FastAKAZEDetectorExtractor" && matcherType == "OpenCVFlannMatcher"){
		return make_shared<ImageAligner<FastAKAZEDetectorExtractor, OpenCVFlannMatcher> >();
	}else if(detectorExtractorType == "OpenCVAKAZEDetectorExtractor" && matcherType == "OpenCVFlannMatcher"){
		return make_shared<ImageAligner<OpenCVAKAZEDetectorExtractor, OpenCVFlannMatcher> >();
	}else if(detectorExtractorType == "CudaAKAZEDetectorExtractor" && matcherType == "OpenCVBFMatcher"){
		return make_shared<ImageAligner<CudaAKAZEDetectorExtractor, OpenCVBFMatcher> >();
	}else if(detectorExtractorType == "CudaAKAZEDetectorExtractor" && matcherType == "OpenCVCudaBFMatcher"){
		return make_shared<ImageAligner<CudaAKAZEDetectorExtractor, OpenCVCudaBFMatcher> >();
	}else if(detectorExtractorType == "CudaAKAZEDetectorExtractor" && matcherType == "CudaAKAZEMatcher"){
		return make_shared<ImageAligner<CudaAKAZEDetectorExtractor, CudaAKAZEMatcher> >();
	}else if(detectorExtractorType == "OpenCVSIFTDetectorExtractor" && matcherType == "OpenCVFlannMatcher"){
		return make_shared<ImageAligner<OpenCVSIFTDetectorExtractor, OpenCVFlannMatcher> >();
	}

	throw runtime_error("Unsupported combination: " + detectorExtractorType + " + " + matcherType);
}
