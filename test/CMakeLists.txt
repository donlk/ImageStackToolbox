cmake_minimum_required(VERSION 2.8)

set(UNIT_TEST_SOURES "unitTests.cpp")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(unitTests ${UNIT_TEST_SOURES})
target_link_libraries(
    unitTests
    ist
    ${GTEST_LIBRARIES}
    ${REQUIRED_OPENCV_LIBS}
    ${FAST_AKAZE_LIBRARY}
    ${CUDA_AKAZE_LIBRARY}
)

add_test(unitTests unitTests ${PROJECT_SOURCE_DIR}/testfiles)

install(TARGETS unitTests DESTINATION bin/test)
