#ifndef GPU_IMAGE_ALIGNER
#define GPU_IMAGE_ALIGNER

#include "ImageAligner.h"
#include "../detectorextractor/CudaAKAZEDetectorExtractor.h"
#include "../matcher/CudaAKAZEMatcher.h"
#include "../matcher/OpenCVBFMatcher.h"
#include "../matcher/OpenCVCudaBFMatcher.h"

class GPUImageAligner: public ImageAligner<CudaAKAZEDetectorExtractor, CudaAKAZEMatcher>{
	public:
		GPUImageAligner();
		~GPUImageAligner();
};

#endif
