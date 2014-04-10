# - Config file for the AuntEater package
# It defines the following variables
#  AuntEater_INCLUDE_DIR  - include directories for AuntEater
#  AuntEater_LIBRARIES    - libraries to link against

#set(AuntEater_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
find_path(AuntEater_INCLUDE_DIR aunteater/Engine.h ${CMAKE_CURRENT_LIST_DIR}/include)

# TODO: Handle more generically the eventual debug suffix
find_library(AuntEater_LIBRARY_RELEASE aunteater ${CMAKE_CURRENT_LIST_DIR}/lib)
find_library(AuntEater_LIBRARY_DEBUG aunteaterd ${CMAKE_CURRENT_LIST_DIR}/lib)

# Handle the _RELEASE and _DEBUG
# see 'cmake --help-module SelectLibraryConfigurations'
include(SelectLibraryConfigurations)
select_library_configurations(AuntEater)

# TODO : does it still make sense in the context of a Config file ?
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AuntEater DEFAULT_MSG AuntEater_INCLUDE_DIR AuntEater_LIBRARY)
