#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <opencv2/opencv.hpp>

class Utils{
	private:
		Utils();
		~Utils();
	public:
		// Compare two images by getting the L2 error (square-root of sum of squared error).
		// Code from: https://github.com/MasteringOpenCV/code/blob/master/Chapter8_FaceRecognition/recognition.cpp
		static double computeImgDifference(const cv::Mat& imgA, const cv::Mat& imgB);

		static cv::Mat computeLaplacian(const cv::Mat& inImg);
};


#endif
