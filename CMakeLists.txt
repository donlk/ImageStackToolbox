# Copyright (c) 2022 András Lehotay-Kéry

cmake_minimum_required(VERSION 2.8)
 
PROJECT(ImageStackToolbox)

# ===================================================================
# Build options
# ===================================================================
OPTION(USE_CUDA "Use CUDA only features" ON)
OPTION(BUILD_NONFREE "Build non-free modules" ON)
OPTION(BUILD_EXAMPLES "Build example executables" ON)
OPTION(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 17)

# ===================================================================
# Sources
# ===================================================================
file(GLOB_RECURSE
    sources
    "src/*.cpp"
)

file(GLOB
    headers
    "inc/*.h"
    "inc/*.hpp"
)

file(GLOB_RECURSE
    test_sources
    "test/*.cpp"
)

# ===================================================================
# Extra flags
# ===================================================================
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
 
# ===================================================================
# External dependencies
# ===================================================================
#find_package(Boost REQUIRED filesystem system)
find_package(CUDA REQUIRED)

set(
	REQUIRED_OPENCV_LIBS
	opencv_core
	opencv_imgproc
	opencv_calib3d
	opencv_highgui
	opencv_features2d
	opencv_flann
	opencv_cudev
	opencv_cudafeatures2d
)
find_package(
	OpenCV REQUIRED
	${REQUIRED_OPENCV_LIBS}
)
find_package(OpenMP)

# ===================================================================
# Third party libraries
# ===================================================================
add_subdirectory(thirdparty)

# ===================================================================
# Use OpenMP if available
# ===================================================================
if(OPENMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    option(USE_OPENMP "Use OpenMP for parallelization" ON)
    add_definitions(-DUSE_OPENMP)
endif(OPENMP_FOUND)

# ===================================================================
# Library construction
# ===================================================================
message("PETTERI_AIMONEN_FOCUS_STACK_INCLUDE_DIR: ${PETTERI_AIMONEN_FOCUS_STACK_INCLUDE_DIR}")
include_directories(
    ${CMDLINE_INCLUDE_DIR}
    ${FAST_AKAZE_INCLUDE_DIR}
    ${CUDA_AKAZE_INCLUDE_DIR}
    ${PETTERI_AIMONEN_FOCUS_STACK_INCLUDE_DIR}
)

add_library(ist ${sources})
target_link_libraries(
    ist
    ${REQUIRED_OPENCV_LIBS}
    ${FAST_AKAZE_LIBRARY}
    ${CUDA_AKAZE_LIBRARY}
)
install(TARGETS ist DESTINATION lib)

# ===================================================================
# Test building
# ===================================================================
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# ===================================================================
# Examples
# ===================================================================
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)
