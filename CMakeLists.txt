# Untested with previous versions, yet should work
cmake_minimum_required(VERSION 2.8.11)

project(aunteater)

## #################################################################
## Setup version numbering
## #################################################################
set(VERSION_MAJOR 0 CACHE STRING "Major version number.")
set(VERSION_MINOR 1 CACHE STRING "Minor version number.")
set(VERSION_BUILD 0 CACHE STRING "Build version number.")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
set(SOVERSION "${VERSION_BUILD}")

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

## #################################################################
## Setup CMake Modules
## #################################################################

list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake"
)

## #################################################################
## Setup output paths
## #################################################################

set(CMAKE_DEBUG_POSTFIX "d")
### from osg CMakeLists.txt
IF(UNIX AND NOT WIN32 AND NOT APPLE)
  IF(CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET(LIB_POSTFIX "64" CACHE STRING "suffix for 32/64 dir placement")
      MARK_AS_ADVANCED(LIB_POSTFIX)
  ENDIF(CMAKE_SIZEOF_VOID_P MATCHES "8")
ENDIF(UNIX AND NOT WIN32 AND NOT APPLE)
IF(NOT DEFINED LIB_POSTFIX)
    SET(LIB_POSTFIX "")
ENDIF(NOT DEFINED LIB_POSTFIX)


if(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY bin)
  set(ARCHIVE_OUTPUT_DIRECTORY lib)
else(WIN32)
  set(RUNTIME_OUTPUT_DIRECTORY bin)
  set(LIBRARY_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
  set(ARCHIVE_OUTPUT_DIRECTORY lib${LIB_POSTFIX})
endif(WIN32)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY    ${CMAKE_BINARY_DIR}/${RUNTIME_OUTPUT_DIRECTORY})

## #################################################################
## Setup the build tools
## #################################################################

# In case we are building with VisualStudio
if(MSVC OR MSVC_IDE) 
  if( MSVC_VERSION LESS 1800 )       # before Visual Studio 2013
    message(FATAL_ERROR "The project requires C++11 features. " 
      "You need at least Visual Studio 12 (Microsoft Visual Studio 2013), " 
      "with Microsoft Visual C++ Compiler Nov 2013 CTP (CTP_Nov2013).") 
  elseif( MSVC_VERSION EQUAL 1800 )  # VS 2013 (VC12)
    message( "VC12: use Microsoft Visual Studio 2013 " 
      "with Microsoft Visual C++ Compiler Nov 2013 CTP (CTP_Nov2013)." ) 
    set(CMAKE_GENERATOR_TOOLSET "CTP_Nov2013" CACHE STRING "Platform Toolset" FORCE) 
  else() # VC12+, assuming C++11 supported. 
    #nothing to do hopefully
  endif() 
endif()


## #################################################################
## Resolve dependencies
## #################################################################
if(APPLE)
  mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
  mark_as_advanced(CMAKE_OSX_SYSROOT)


else(APPLE)

endif(APPLE)

# Allows the libraries contained in the current project to expose their headers
# to all the source files of the project (syntex eg. #include <{$libname}/${libfile}>)
include_directories(src/libs/)

# Directory where custom headers are exported.
# It is notably where ${libname}_Export.h files will be exported for DLL libraries,
#   and those file must be seen for libraries and clients compilations.
include_directories(${CMAKE_BINARY_DIR}/include)

#
# Boost
#

# Use this variable to hint where to find boost when it's not system wide
set(BOOST_ROOT CACHE PATH "Path to Boost library")

set(boost_binaries 
#system 
#serialization
)

if (WIN32)
    # By default, boost seems to be compiled as static archive on Windows platform
    # just trying to anticipate, since static archives are not found if that is set to false
    option(BUILD_WITH_BOOST_STATIC_LIBS "Link with static Boost libraries" ON)
    if(BUILD_WITH_BOOST_STATIC_LIBS)
        # It is not clear why on Windows we need to list those extra libraries
        # Is it because it finds them silently on *n*x platforms ?
        list(APPEND boost_binaries thread date_time chrono)
    else(BUILD_WITH_BOOST_STATIC_LIBS)
    set(boost_binaries system serialization)
    endif(BUILD_WITH_BOOST_STATIC_LIBS)
else (WIN32)
    option(BUILD_WITH_BOOST_STATIC_LIBS "Link with static Boost libraries" OFF)
endif (WIN32)

set(Boost_USE_STATIC_LIBS ${BUILD_WITH_BOOST_STATIC_LIBS})
find_package(Boost 1.49 COMPONENTS ${boost_binaries})

##
## Cpputest
##

find_package(Cpputest)
if (WIN32 AND CPPUTEST_FOUND)
    # The Winmm.lib is required on Windows, because UtestPlatform.obj
    # references __imp__timeGetTime@0 in function _PlatformSpecificMemset
    list(APPEND Cpputest_LIBRARIES Winmm.lib)
endif (WIN32 AND CPPUTEST_FOUND)

##
## glfw
##

## This is recommanded by the documentation, but then there is a problem when linking to glfw
## see: http://www.glfw.org/docs/latest/build.html#build_link_cmake_pkgconfig
#find_package(PkgConfig REQUIRED)
#pkg_search_module(GLFW REQUIRED glfw3)

## There is also a glfwTargets.cmake distributed, but it is probably not used with this invocation.
find_package(GLFW)
## Find OpenGL explictily, but I suspect it is supposed to be handled by glfw if imported correclty.
find_package(OpenGL)

find_package(JPEG)

## #################################################################
## Build options
## #################################################################
include (cmc-macros)

# CMake automatically checks this variable value when calling add_library command.
#option(BUILD_SHARED_LIBS "Build shared libraries" True)
set(BUILD_SHARED_LIBS False)

# 
# C++14 support
# 
option(BUILD_WITH_C++14_SUPPORT "Set the compiler flags/options required to compile with C++14 support" true)
if(BUILD_WITH_C++14_SUPPORT)
    IF(UNIX)
        # Boost::Serialization usage exceeds the default 128 depth for template instantiation
        LIST(APPEND CMAKE_CXX_FLAGS "-std=c++1y -ftemplate-depth=512")
    ENDIF(UNIX)
endif(BUILD_WITH_C++14_SUPPORT)

if (CMAKE_GENERATOR STREQUAL "Xcode")
    SET(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
endif ()

## Doxygen documentation
#option(BUILD_DOCUMENTATION "Build doxygen's documentation" false)
#conditional_add_subdirectory(docs OPTIONS BUILD_DOCUMENTATION)

# Start recursive crawling of the sources
add_subdirectory(src)

