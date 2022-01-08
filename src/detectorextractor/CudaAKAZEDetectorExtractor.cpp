#include "../../inc/detectorextractor/CudaAKAZEDetectorExtractor.h"

#include <cuda_akaze/src/lib/utils.h>

using namespace std;

CudaAKAZEDetectorExtractor::CudaAKAZEDetectorExtractor(){
	// Only binary descriptor is implemented as of now for cuda-akaze
	options.descriptor = DESCRIPTOR_TYPE::MLDB;
	options.descriptor_size = 0;
	options.descriptor_channels = 3;
	options.dthreshold = 0.00001f;
	options.omax = 4;
	options.nsublevels = 4;
	options.diffusivity = DIFFUSIVITY_TYPE::PM_G2;
}

CudaAKAZEDetectorExtractor::~CudaAKAZEDetectorExtractor(){
	// NOOP
}

void CudaAKAZEDetectorExtractor::detectAndCompute(
	cv::Mat img,
	std::vector<cv::KeyPoint>& outKeypoints,
	cv::Mat& outDescriptors
){
	cv::Mat imgGray, imgFloat;
	cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);
	imgGray.convertTo(imgFloat, CV_32F, 1.0/255.0, 0);
	options.img_width = img.cols;
	options.img_height = img.rows;

	libAKAZECU::AKAZE evolution(options);

	evolution.Create_Nonlinear_Scale_Space(imgFloat);
	evolution.Feature_Detection(outKeypoints);
	evolution.Compute_Descriptors(outKeypoints, outDescriptors);

}
