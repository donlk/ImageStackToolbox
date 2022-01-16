ImageStackToolbox
=================

ImageStackToolbox is a container library for all stack algorithms working with images. The library provides interfaces for image detectors/descriptors, matchers and stacker classes.
There arew two ways to use the library:
 1. Doing the feature point detection/description through IST with the help of the helper classes and then doing the image stacking. 
 2. or doing the feature point detection/description through an external tool.

For the first use-case, one should simply use `ImageStackerBase` that provides convenient `cv::Mat` types for image stacking. For the second use-case, `GenericImageStackerBase` should be used, that simply provides the paths for all images waiting for stacking.

#### Dependencies
------------
 - OpenCV (`core,imgproc,calib3d,highgui,features2d,flann,video,photo,cudev,cudafeatures2d`)
 - GTest (for unit tests)

#### Building
------------
```
mkdir .build
cd .build
cmake ../ -DOpenCV_DIR=<installed_opencv_dir> -DGTEST_ROOT=<installed_gtest_dir>
```

 -  Notes:
    - To prevent using unsupported GCC versions for CUDA libraries, configure the project with the following CMake flag:\
    `-DCUDA_HOST_COMPILER=/usr/bin/gcc-${GCC_VERSION}`

#### Running
------------
Two example applications are provided under the `examples` folder. Both share a similar trait: they provide a convenient way to operate on a folder where the the images are ordered in a way that each "stack image block" follows the other. This means that when an image difference in a stack is above a certain threshold (average * 2), the images will be stacked, then the program moves on to the next stack, computing the image difference again, and so on.
 - **BatchFocusStackExample**: Uses standard feature detection/description/matching and a focus stacking technique inspired by [this algorithm](https://github.com/cmcguinness/focusstack).
   - `IST_BatchFocusStackExample -i <input_folder> -o <output_folder>`
 - **BatchPetteriAimonenFocusStackExample**: Uses an enclosed focus stacking algorithm using the [following library](https://github.com/PetteriAimonen/focus-stack).
   - `IST_BatchPetteriAimonenFocusStackExample -i <input_folder> -o <output_folder>`
