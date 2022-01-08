ImageStackToolbox
=================

BUILDING
--------

To prevent using unsupported GCC versions for CUDA libraries, configure the project with the following CMake flag:
-DCUDA_HOST_COMPILER=/usr/bin/gcc-${GCC_VERSION}
