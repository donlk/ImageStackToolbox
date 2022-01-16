#include "FileUtils.hpp"

#include "../inc/image/Image.h"
#include "../inc/util/Timer.h"
#include "../inc/util/ImageUtils.h"
#include "../inc/imagestack/PetteriAimonenFocusImageStacker.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include <cmdline.h>

#include <string>
#include <vector>
#include <iostream>

#if(defined(_MSC_VER) or (defined(__GNUC__) and (7 <= __GNUC_MAJOR__)))
	#include <filesystem>
	namespace fs = ::std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = ::std::experimental::filesystem;
#endif

using namespace std;

const int OUT_FILENAME_PADDING = 8;

int main(int argc, char** argv){
	cmdline::parser cmdLineParser;

	cmdLineParser.add<string>("input-image-folder", 'i', "The input image folder", true, "");
	cmdLineParser.add<string>("output-image-folder", 'o', "The output image folder", true, "");

	cmdLineParser.parse_check(argc, argv);

	fs::path inFolderPath(cmdLineParser.get<string>("input-image-folder"));
	fs::path outFolderPath(cmdLineParser.get<string>("output-image-folder"));

	if(!fs::is_directory(inFolderPath)){
		cerr<< "ERROR: Provided image folder is not a directory: " << inFolderPath.string() << endl;
		return EXIT_FAILURE;
	}

	if(!fs::is_directory(outFolderPath)){
		cout << "Output directory doesn't exist, creating: " << outFolderPath.string() << endl;
		fs::create_directory(outFolderPath);
	}

	vector<fs::path> imgFilePaths = loadImagePaths(inFolderPath.string());
	if(imgFilePaths.size() < 2){
		cerr << "ERROR: At least 2 images are needed for focus stacking." << std::endl;
		return EXIT_FAILURE;
	}

	cout << "Images in directory: " << imgFilePaths.size() << endl;

	Timer timer;
	timer.start();

	auto stacker = make_shared<PetteriAimonenFocusImageStacker>();
	vector<shared_ptr<Image>> imgGroup;

	//bool stopLoop = false;
	int stackedImgCount = 0;
	double imageDiffSumPerCluster = 0;
	double imageDiffAvgPerCluster = 0;
	for(size_t i = 0; i < imgFilePaths.size() - 1; ++i){
		//cout << "New base image: " << imgFilePaths[i].filename().string() << endl;
		shared_ptr<Image> baseImg = make_shared<Image>(
			imgFilePaths[i].string(),
			imgFilePaths[i].filename().string(),
			imgFilePaths[i].extension().string(),
			cv::imread(imgFilePaths[i].string())
		);

		const shared_ptr<Image> targetImg = make_shared<Image>(
			imgFilePaths[i+1].string(),
			imgFilePaths[i+1].filename().string(),
			imgFilePaths[i+1].extension().string(),
			cv::imread(imgFilePaths[i+1].string())
		);

		const double diff = ImageUtils::computeImgDifference(baseImg->getMat(), targetImg->getMat());
		cout << targetImg->getName() << " diff: " << diff << endl;

		bool isNewImageCluster = false;
		if(imgGroup.size() == 0){
			// If the current cluster container is empty, add the first and the next image
			// to the cluster automatically (according to our initial assumption that the imageset
			// has to have at least 2 images for every stack), and also make the current difference
			// the initial average.
			imgGroup.push_back(baseImg);
			imgGroup.push_back(targetImg);
			imageDiffSumPerCluster = diff;
			imageDiffAvgPerCluster = diff;
			cout << "New cluster start image: [" << baseImg->getName() << "]" << endl;
		}else if(diff > imageDiffAvgPerCluster * 2){
			// If the current difference is greater than some threshold (average*2),
			// it's a new image cluster. The threshold here could be improved, it might not
			// be ideal for all datasets.
			isNewImageCluster = true;
		}else{
			imgGroup.push_back(targetImg);
			imageDiffSumPerCluster += diff;
			imageDiffAvgPerCluster = imageDiffSumPerCluster / imgGroup.size();
		}

		// If there's is no new image cluster, continue.
		if(!isNewImageCluster && i < imgFilePaths.size() - 2){
			continue;
		}

		cout << "Difference threshold reached for [" << targetImg->getName() << "]:" << diff << endl;
		cout << endl;

		vector<std::string> imageGroupPaths;
		for(auto image: imgGroup){
			imageGroupPaths.push_back(image->getPath());
		}

		std::ostringstream ss;
		ss << std::setw(OUT_FILENAME_PADDING) << std::setfill('0') << stackedImgCount;
		string outFile = string(
			outFolderPath.string()
			+ "/"
			+ ss.str()
			+ baseImg->getExtension()
		);

		stacker->stackImages(imageGroupPaths, outFile);

		stackedImgCount++;

		// Reset
		imageDiffSumPerCluster = 0;
		imageDiffAvgPerCluster = 0;
		imgGroup.clear();
	}

	cout << "Overall TIME: " << timer.getElapsedMillis().count() << "ms" << endl;

	return EXIT_SUCCESS;
}
