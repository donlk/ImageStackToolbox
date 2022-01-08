#include "../../inc/util/Utils.h"

#include <opencv2/cudafilters.hpp>
#include <opencv2/core/core_c.h>

using namespace std;

double Utils::computeImgDifference(const cv::Mat& imgA, const cv::Mat& imgB){
	if(imgA.rows > 0 && imgA.rows == imgB.rows && imgA.cols > 0 && imgA.cols == imgB.cols){
		// Calculate the L2 relative error between the 2 images.
		double errorL2 = norm(imgA, imgB, CV_L2);
		// Convert to a reasonable scale, since L2 error is summed across all pixels of the image.
		double difference = errorL2 / (double) (imgA.rows * imgA.cols);
		return difference;
	}else{
		return 1; // Return 1, indicating extensive difference
	}
}

cv::Mat Utils::computeLaplacian(const cv::Mat& inImg){
	// Generally, keeping these two values the same or very close works well
	int kernelSize = 9;     // Size of the laplacian window
	int blurSize = 9;       // How big of a kernel to use for the gaussian blur

	cv::Mat inImgGray;
	cv::cvtColor(inImg, inImgGray, cv::COLOR_BGR2GRAY);

	cv::Mat outImg;
	cv::Mat blurredImg;
	// TODO: Optimize wit single image
	cv::GaussianBlur(inImgGray, blurredImg, cv::Size(blurSize, blurSize), 0);
	cv::Laplacian(blurredImg, outImg, CV_64F, kernelSize);

	/*cv::cuda::GpuMat inImgGpu, blurredImgGpu, outImgGpu;
	inImgGpu.upload(inImg);
	auto gaussFilter = cv::cuda::createGaussianFilter(inImgGpu.type(), blurredImgGpu.type(), cv::Size(blurSize, blurSize), 0);
	gaussFilter->apply(inImgGpu, blurredImgGpu);

	auto laplacianFilter = cv::cuda::createLaplacianFilter(blurredImgGpu.type(), outImgGpu.type(), 3);
	laplacianFilter->apply(blurredImgGpu, outImgGpu);

	outImgGpu.download(outImg);*/

	return outImg;
}
