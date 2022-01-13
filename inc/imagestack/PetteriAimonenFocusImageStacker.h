#ifndef PETTERI_AIMONEN_FOCUS_IMAGE_STACKER
#define PETTERI_AIMONEN_FOCUS_IMAGE_STACKER

#include <opencv2/opencv.hpp>

#include <vector>
#include <memory>

#include "GenericImageStackerBase.h"

class PetteriAimonenFocusImageStacker: public GenericImageStackerBase{
	public:
		PetteriAimonenFocusImageStacker();
		virtual ~PetteriAimonenFocusImageStacker();

		void stackImages(
			const std::vector<std::string> inImgPaths,
			const std::string outImgPath
		) override;
};

#endif
