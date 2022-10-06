// Copyright (c) 2022 András Lehotay-Kéry

#include "../../inc/image/Image.h"

using namespace std;

Image::Image(const string& path, const string& name, const string& extension, cv::Mat mat):
	path(path), name(name), extension(extension), mat(mat)
{
	// Intentionally NOOP
}

Image::~Image(){
	// Intentionally NOOP
}
