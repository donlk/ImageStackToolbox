#ifndef MEAN_IMAGE_STACKER
#define MEAN_IMAGE_STACKER

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

#include "ImageStackerBase.h"

class MeanImageStacker: public ImageStackerBase{
	public:
		MeanImageStacker();
		virtual ~MeanImageStacker();

		cv::Mat stackImages(std::vector<cv::Mat> inImgs) override;
};

#endif
