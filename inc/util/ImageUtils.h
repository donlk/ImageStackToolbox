// Copyright (c) 2022 András Lehotay-Kéry

#ifndef IMAGE_UTILS
#define IMAGE_UTILS

#include "../image/Image.h"

#include <opencv2/opencv.hpp>

#include <vector>

class ImageUtils{
	public:
		/**
		** Reads all provided image paths and constructs a vector filled with parsed 'Image' instances.
		**/
		static std::vector<std::shared_ptr<Image>> loadImages(const std::vector<std::string>& imagePaths);

		// Compare two images by getting the L2 error (square-root of sum of squared error).
		// Code from: https://github.com/MasteringOpenCV/code/blob/master/Chapter8_FaceRecognition/recognition.cpp
		static double computeImgDifference(const cv::Mat& imgA, const cv::Mat& imgB);

		static cv::Mat computeLaplacian(const cv::Mat& inImg);

		static std::vector<std::string> exportImagesToDir(
			const std::string& outputDir,
			const std::vector<cv::Mat>& images,
			const int fileNamePadding
		);
};


#endif
