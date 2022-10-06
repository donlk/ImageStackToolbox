// Copyright (c) 2022 András Lehotay-Kéry

#ifndef MEAN_IMAGE_STACKER
#define MEAN_IMAGE_STACKER

#include "ImageStackerBase.h"

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

class MeanImageStacker: public ImageStackerBase{
	public:
		MeanImageStacker();
		virtual ~MeanImageStacker();

		cv::Mat stackImages(std::vector<cv::Mat> inImgs) override;
};

#endif
