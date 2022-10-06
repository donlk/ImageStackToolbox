// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/imagestack/MeanImageStacker.h"
#include "../../inc/image/Image.h"
#include "../../inc/util/ImageUtils.h"
#include "../../inc/util/Timer.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

MeanImageStacker::MeanImageStacker(){
	// NOOP
}

MeanImageStacker::~MeanImageStacker(){
	// NOOP
}

cv::Mat MeanImageStacker::stackImages(std::vector<cv::Mat> inImgs){
	cout << "CVMatMeanImageStacker started..." << endl;

	Timer timer;
	timer.start();

	// To prevent overflow, we use CV_64FC3 image type.
	// Based on the idea from:
	// https://stackoverflow.com/questions/35668074/how-i-can-take-the-average-of-100-image-using-opencv
	cv::Mat outImg(inImgs[0].rows, inImgs[0].cols, CV_64FC3);
	outImg.setTo(cv::Scalar(0, 0, 0, 0));

	cv::Mat temp;
	for_each(
		inImgs.begin(),
		inImgs.end(),
		[&outImg, &temp](const cv::Mat& inImg){
			// To match the destination image, convert the source image to CV_64FC3 as well.
			inImg.convertTo(temp, CV_64FC3);
			cv::accumulate(temp, outImg);
		}
	);

	// Convert back to CV_8UC3 type, applying the division to get the actual mean
	outImg.convertTo(outImg, CV_8U, 1. / inImgs.size());

	cout << "MeanImageStacker finished. TIME: " << timer.getElapsedMillis().count() << "ms" << endl;

	return outImg;
}
