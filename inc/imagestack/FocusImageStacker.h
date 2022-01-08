#ifndef FOCUS_IMAGE_STACKER
#define FOCUS_IMAGE_STACKER

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

#include "ImageStackerBase.h"

class FocusImageStacker: public ImageStackerBase{
	public:
		FocusImageStacker();
		virtual ~FocusImageStacker();

		cv::Mat stackImages(std::vector<cv::Mat> inImgs) override;
};

#endif
