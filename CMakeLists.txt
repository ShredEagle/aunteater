cmake_minimum_required(VERSION 3.15)

# Setting the VERSION on root project() will populate CMAKE_PROJECT_VERSION
# see: https://cmake.org/cmake/help/v3.13/variable/CMAKE_PROJECT_VERSION.html
project(Aunteater VERSION "${BUILD_VERSION}")

# Setup cmake helpers in 'cmake' submodule
include ("cmake/include.cmake")


##
## Build options
##

# Common build settings
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

#### TODEL
##
## Cpputest
##

#find_package(Cpputest)
#if (WIN32 AND CPPUTEST_FOUND)
#    # The Winmm.lib is required on Windows, because UtestPlatform.obj
#    # references __imp__timeGetTime@0 in function _PlatformSpecificMemset
#    list(APPEND Cpputest_LIBRARIES Winmm.lib)
#endif (WIN32 AND CPPUTEST_FOUND)
#####

##
## Include components
##

add_subdirectory(src)
