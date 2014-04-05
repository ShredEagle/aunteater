project(nowave)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
#configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
#        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
#        @ONLY)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    Player.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    Player.cpp
)


add_executable(${PROJECT_NAME}
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
)

set(Polycode CACHE PATH "Path to Polycode")
set(Polycode_LIBRARIES "Polycore_d.lib")
set(Polycode_LIBRARIES_DEPENDENCIES "Polycore_d.lib;zlibd.lib;freetype_d.lib;liboggd.lib;libvorbisd.lib;libvorbisfiled.lib;OpenAL32d.lib;physfsd.lib;libpng15_staticd.lib")
set(Polycode_LIBRARIES_WIN "opengl32.lib;glu32.lib;winmm.lib;ws2_32.lib")

include_directories(
    ${Polycode}Core/Include
    ${Polycode}Core/Dependencies/include
    ${Polycode}Core/PolycodeView
    ${Polycode}Core/Dependencies/include/AL
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    ${Polycode_LIBRARIES}
    ${Boost_LIBRARIES}
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
        LINK_FLAGS  "/LIBPATH:${Polycode}/Core/lib;${Polycode}/Modules/lib;${Polycode}/Modules/Dependencies/lib;${Polycode}/Core/Dependencies/lib;"
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)
