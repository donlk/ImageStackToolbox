ImageStackToolbox
=================

ImageStackToolbox is a container library for all stack algorithms working with images. The library provides interfaces for image detectors/descriptors, matchers and stacker classes.
There arew two ways to use the library:
 1. Doing the feature point detection/description through IST with the help of the helper classes and then doing the image stacking. 
 2. or doing the feature point detection/description through an external tool.

For the first use-case, one should simply use `ImageStackerBase` that provides convenient `cv::Mat` types for image stacking. For the second use-case, `GenericImageStackerBase` should be used, that simply provides the paths for all images waiting for stacking.

#### Dependencies
------------
 - OpenCV
 - GTest (for unit tests)

#### Building
------------
```
mkdir .build
cd .build
cmake ../ -DOpenCV_DIR=<installed_opencv_dir> -DGTEST_ROOT=<installed_gtest_dir>
```

##### Notes:
 - To prevent using unsupported GCC versions for CUDA libraries, configure the project with the following CMake flag:
-DCUDA_HOST_COMPILER=/usr/bin/gcc-${GCC_VERSION}
