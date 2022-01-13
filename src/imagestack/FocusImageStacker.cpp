//This algorithm was inspired by the high-level description given at
//
//http://stackoverflow.com/questions/15911783/what-are-some-common-focus-stacking-algorithms

#include "../../inc/imagestack/FocusImageStacker.h"
#include "../../inc/image/Image.h"
#include "../../inc/util/ImageUtils.h"
#include "../../inc/util/Timer.h"

#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

FocusImageStacker::FocusImageStacker(){
	// NOOP
}

FocusImageStacker::~FocusImageStacker(){
	// NOOP
}

cv::Mat FocusImageStacker::stackImages(std::vector<cv::Mat> inImgs){
	cout << "Computing the laplacian of the blurred images" << endl;

	vector<cv::Mat> laplacianImages;
	laplacianImages.resize(inImgs.size());
#ifdef USE_OPENMP
  #pragma omp parallel for schedule(dynamic)
#endif
	for(size_t i = 0; i < inImgs.size(); ++i){
		//cout << "Laplacian [" << i << "/" << images.size() << "]" << endl;
		cv::Mat laplacianImg = ImageUtils::computeLaplacian(inImgs[i]);

#ifdef USE_OPENMP
  #pragma omp critical
#endif
		{
			// TODO: The pixel evaluation after does not work correctly if we merely
			// push the image into the container. Investigate why keeping the initial
			// ordering matters here.
			laplacianImages[i] = laplacianImg;
			//laplacianImages.push_back(laplacianImg);
		}

		/*cv::namedWindow("laplac", cv::WINDOW_NORMAL);
		cv::resizeWindow("laplac", imgLap.cols / 3, imgLap.rows / 3);
		cv::imshow("laplac", imgLap);
		cv::waitKey(0);*/
	}

	cv::Mat outImg = cv::Mat::zeros(
		inImgs[0].rows,
		inImgs[0].cols,
		inImgs[0].type()
	);

	Timer timer;
	timer.start();


#ifdef USE_OPENMP
  #pragma omp parallel for schedule(dynamic)
#endif
	for(int y = 0; y < outImg.rows; ++y){
		cv::Vec3b* pixelPerRow = outImg.ptr<cv::Vec3b>(y);
		for(int x = 0; x < outImg.cols; ++x){
			double maxIntensity = numeric_limits<double>::min();
			int maxIntensityIdx = 0;
			for(size_t k = 0; k < laplacianImages.size(); ++k){
				double absIntensity = abs(laplacianImages[k].at<double>(y, x));
				if(absIntensity > maxIntensity){
					maxIntensity = absIntensity;
					maxIntensityIdx = k;
				}
			}
			pixelPerRow[x] = inImgs[maxIntensityIdx].at<cv::Vec3b>(cv::Point(x,y));
		}
	}

	cout << "Matrix assembly TIME: " << timer.getElapsedMillis().count() << "ms" << endl;

	return outImg;
}
