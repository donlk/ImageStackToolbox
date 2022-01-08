#ifndef IMAGE
#define IMAGE

#include <string>
#include <opencv2/opencv.hpp>

class Image{
	public:
		Image(const std::string& path, const std::string& name, const std::string& extension, cv::Mat mat);
		~Image();

		std::string getName(){
			return name;
		}

		std::string getPath(){
			return path;
		}

		std::string getExtension(){
			return extension;
		}

		cv::Mat getMat(){
			return mat;
		}

	private:
		std::string path;
		std::string name;
		std::string extension;
		cv::Mat mat;

};

#endif
