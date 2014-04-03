## CMAKE_DOCUMENTATION_START FindCpputest.cmake
##
## Try to find Cpputest.
## Once done this will define :
##  \\li Cpputest_FOUND - system has Cpputest
##  \\li Cpputest_INCLUDE_DIR - the Cpputest include directory
##  \\li Cpputest_LIBRARIES - The libraries needed to use Cpputest
##  \\li Cpputest_LIBRARY - The Cpputest library
##
## You can use the CPPUTEST_DIR environment variable.
##
## CMAKE_DOCUMENTATION_END

##
## Use the CPPUTEST_DIR environment variable
##
set(Cpputest_DIR $ENV{CPPUTEST_DIR} CACHE PATH "Path to Cpputest" )

##
## Look for headers and libs
##
find_path(Cpputest_INCLUDE_DIR CppUTest/TestHarness.h
    ${Cpputest_DIR}/include
    ${Cpputest_DIR}
    $ENV{Cpputest_DIR}
    NO_DEFAULT_PATH
  )

find_path(Cpputest_INCLUDE_DIR CppUTest/TestHarness.h
    $ENV{Cpputest_HOME}/include
    $ENV{Cpputest_ROOT}/include
    /usr/local/include
    /usr/include
  )

find_library(Cpputest_LIBRARY 
    NAMES libCppUTest CppUTest
    PATHS
      ${Cpputest_DIR}
      ${Cpputest_DIR}/lib
      ${Cpputest_DIR}/lib/release
      ${Cpputest_DIR}/bin
    NO_DEFAULT_PATH
  )

find_library(Cpputest_LIBRARY 
    NAMES libCppUTest CppUTest
    PATHS
    /usr/lib64
)

##	
## handle the QUIETLY and REQUIRED arguments and set Cpputest_FOUND to TRUE if 
## all listed variables are TRUE
##
INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Cpputest DEFAULT_MSG Cpputest_INCLUDE_DIR Cpputest_LIBRARY)

#there seems to be a bug : xxx_FOUND is always output in upper case
IF(CPPUTEST_FOUND)
  SET( Cpputest_LIBRARIES ${Cpputest_LIBRARY})
ELSE(CPPUTEST_FOUND)
  SET( Cpputest_LIBRARIES )
ENDIF(CPPUTEST_FOUND)

MARK_AS_ADVANCED( Cpputest_INCLUDE_DIR Cpputest_LIBRARIES )
