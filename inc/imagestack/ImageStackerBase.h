#ifndef IMAGE_STACKER_BASE
#define IMAGE_STACKER_BASE

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

class ImageStackerBase{
	public:
		ImageStackerBase();
		virtual ~ImageStackerBase();

		virtual cv::Mat stackImages(std::vector<cv::Mat> inImgs) = 0;
};

#endif
