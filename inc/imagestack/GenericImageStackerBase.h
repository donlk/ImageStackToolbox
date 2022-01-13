#ifndef GENERIC_IMAGE_STACKER_BASE
#define GENERIC_IMAGE_STACKER_BASE

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

class GenericImageStackerBase{
	public:
		GenericImageStackerBase();
		virtual ~GenericImageStackerBase();

		virtual void stackImages(std::vector<std::string> inImgPaths, const std::string outImgPath) = 0;
};

#endif
