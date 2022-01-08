#ifndef IMAGE_ALIGNER
#define IMAGE_ALIGNER

#include "../detectorextractor/DetectorExtractorBase.h"
#include "../image/Image.h"
#include "../matcher/Matcher.h"
#include "../util/Timer.h"

#include <vector>
#include <memory>

template<class DetectorExtractorType, class MatcherType>
class ImageAligner{
	static_assert(
		std::is_base_of<DetectorExtractorBase, DetectorExtractorType>::value,
		"DetectorExtractorType must inherit from DetectorExtractorBase!"
	);

	static_assert(
		std::is_base_of<Matcher, MatcherType>::value,
		"MatcherType must inherit from MatcherBase!"
	);


	public:
		ImageAligner();
		virtual ~ImageAligner();

		std::vector<cv::Mat> alignImages(std::vector<std::shared_ptr<Image> > inImgs);

	private:
		const float INLIER_ERROR_THRESHOLD = 2.5f;
		const float MATCH_DISTANCE_RATIO_THRESHOLD = 0.8f;

		std::shared_ptr<DetectorExtractorBase> detectorExtractor;
		std::shared_ptr<Matcher> matcher;

		Timer timer;
};

#endif
