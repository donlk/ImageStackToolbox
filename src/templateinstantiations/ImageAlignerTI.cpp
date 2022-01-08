#include "../imagealign/ImageAligner.cpp"

#include "../../inc/detectorextractor/CudaAKAZEDetectorExtractor.h"
#include "../../inc/detectorextractor/FastAKAZEDetectorExtractor.h"
#include "../../inc/detectorextractor/OpenCVAKAZEDetectorExtractor.h"
#include "../../inc/matcher/CudaAKAZEMatcher.h"
#include "../../inc/matcher/OpenCVBFMatcher.h"
#include "../../inc/matcher/OpenCVCudaBFMatcher.h"
#include "../../inc/matcher/OpenCVFlannMatcher.h"
#include "../../inc/detectorextractor/OpenCVSIFTDetectorExtractor.h"

template class ImageAligner<FastAKAZEDetectorExtractor, OpenCVFlannMatcher>;
template class ImageAligner<OpenCVAKAZEDetectorExtractor, OpenCVFlannMatcher>;
template class ImageAligner<CudaAKAZEDetectorExtractor, OpenCVBFMatcher>;
template class ImageAligner<CudaAKAZEDetectorExtractor, OpenCVCudaBFMatcher>;
template class ImageAligner<CudaAKAZEDetectorExtractor, CudaAKAZEMatcher>;
template class ImageAligner<OpenCVSIFTDetectorExtractor, OpenCVFlannMatcher>;
