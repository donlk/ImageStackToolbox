# Copyright (c) 2022 András Lehotay-Kéry

# cmdline
set(CMDLINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmdline" PARENT_SCOPE)

# Fast-AKAZE
add_subdirectory(fast_akaze/fast_akaze)
set(FAST_AKAZE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
set(FAST_AKAZE_LIBRARY fast_akaze PARENT_SCOPE)

# CUDA-AKAZE
if(USE_CUDA)
    set(BUILD_EXAMPLES OFF)
    add_subdirectory(cuda_akaze)
    set(CUDA_AKAZE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cuda_akaze/src/lib PARENT_SCOPE)
    set(CUDA_AKAZE_LIBRARY AKAZE AKAZE_CUDA PARENT_SCOPE)
endif(USE_CUDA)

set(BUILD_TESTS OFF)
add_subdirectory(petteri_aimonen_focus_stack)
set(PETTERI_AIMONEN_FOCUS_STACK_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/petteri_aimonen_focus_stack/src PARENT_SCOPE)
set(PETTERI_AIMONEN_FOCUS_STACK_LIBRARY focus_stack PARENT_SCOPE)
