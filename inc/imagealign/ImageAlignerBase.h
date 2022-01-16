#ifndef IMAGE_ALIGNER_BASE
#define IMAGE_ALIGNER_BASE

#include "../image/Image.h"

#include <vector>
#include <memory>

class ImageAlignerBase{
	public:
		ImageAlignerBase();
		virtual ~ImageAlignerBase();

		virtual std::vector<cv::Mat> alignImages(std::vector<std::shared_ptr<Image> > inImgs) = 0;
};

#endif
