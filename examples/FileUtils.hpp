#ifndef EXAMPLES_FILEUTILS
#define EXAMPLES_FILEUTILS

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#if defined(CXX17_FILESYSTEM) || defined (CXX17_FILESYSTEM_LIBFS)
	#include <filesystem>
	namespace fs = std::filesystem;
#elif defined(CXX11_EXP_FILESYSTEM) || defined (CXX11_EXP_FILESYSTEM_LIBFS)
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

namespace fs = std::filesystem;

std::string supportedImgFormats[] = {".png", ".jpg", ".jpeg"};

bool isImgExtensionSupported(const std::string& ext){
	return find(begin(supportedImgFormats), end(supportedImgFormats), ext) != end(supportedImgFormats);
}

std::vector<fs::path> loadImagePaths(const std::string& directoryPath){
	// List the file paths into a boos container to make path segmentation trivial.
	std::vector<fs::directory_entry> fileEntries;
	copy(
		fs::directory_iterator(std::string(directoryPath)),
		fs::directory_iterator(),
		back_inserter(fileEntries)
	);

	std::vector<fs::path> imgFilePaths;
	for(auto it = fileEntries.begin(); it != fileEntries.end(); ++it){
		std::string extension = fs::path(it->path().extension());
		if(!isImgExtensionSupported(extension)){
			std::cerr <<
				"Unsupported image extension: "
				<< it->path().string()
				<< "\nSupported formats:"
				<< supportedImgFormats
			<< std::endl;
			continue;
		}
		imgFilePaths.push_back(it->path());
	}

	std::sort(imgFilePaths.begin(), imgFilePaths.end());

	return imgFilePaths;
}


#endif
