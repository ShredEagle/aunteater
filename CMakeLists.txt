cmake_minimum_required(VERSION 3.16)

# Setting the VERSION on root project() will populate CMAKE_PROJECT_VERSION
# see: https://cmake.org/cmake/help/v3.13/variable/CMAKE_PROJECT_VERSION.html
project(Aunteater VERSION "${BUILD_VERSION}")

# Setup cmake helpers in 'cmake' submodule
include ("cmake/include.cmake")

cmc_include_conan_configuration()


##
## Include components
##

include(cmc-install)
cmc_install_root_component_config(${PROJECT_NAME})
cmc_register_source_package(${PROJECT_NAME})

add_subdirectory(src)
