#include "../inc/util/Utils.h"

#include <string>

#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

std::string testsetFolderPath;

TEST(ISTTest, ImageDifference){
	std::string imgAPath = testsetFolderPath + "/img_difference_A.jpg";
	std::string imgBPath = testsetFolderPath + "/img_difference_B.jpg";

	cv::Mat imgA = cv::imread(imgAPath);
	cv::Mat imgB = cv::imread(imgBPath);

	const double difference = Utils::computeImgDifference(imgA, imgB);
	EXPECT_DOUBLE_EQ(difference, 0.0093378662128897096);
}

TEST(ISTTest, ImageLaplacian){
	cv::Mat mat = cv::Mat(3, 3, CV_8UC3, cv::Scalar(255,255,255));
	mat.at<cv::Vec3b>(0, 0) = cv::Vec3b(190,69,139);
	mat.at<cv::Vec3b>(0, 1) = cv::Vec3b(12,89,139);
	mat.at<cv::Vec3b>(0, 2) = cv::Vec3b(80,234,35);
	mat.at<cv::Vec3b>(1, 0) = cv::Vec3b(60,102,150);
	mat.at<cv::Vec3b>(1, 1) = cv::Vec3b(4,45,56);
	mat.at<cv::Vec3b>(1, 2) = cv::Vec3b(23,12,250);
	mat.at<cv::Vec3b>(2, 0) = cv::Vec3b(19,69,139);
	mat.at<cv::Vec3b>(2, 1) = cv::Vec3b(67,50,139);
	mat.at<cv::Vec3b>(2, 2) = cv::Vec3b(19,8,139);

	cv::Mat laplacianMat = Utils::computeLaplacian(mat);

	cv::Vec3d laplacianSumVector;
	cv::reduce(laplacianMat, laplacianSumVector, 1, cv::REDUCE_SUM, CV_64F);

	EXPECT_EQ(laplacianSumVector[0], -7680);
	EXPECT_EQ(laplacianSumVector[1], 0);
	EXPECT_EQ(laplacianSumVector[2], 7680);
}
 
int main(int argc, char **argv){
	if(argc < 2){
		std::cerr << "Usage: unitTests <testset_folder>" << std::endl;
		return EXIT_FAILURE;
	}
	testsetFolderPath = argv[1];

	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
