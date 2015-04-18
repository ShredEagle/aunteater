project(OpenGL_samples)


# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    CImg.h
    DrawingPolygons.h
    Globals.h
    ImageReader.h
    Textures.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    ImageReader.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})
 
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIR} ${JPEG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${JPEG_LIBRARIES})

configure_file(${CMAKE_SOURCE_DIR}/resources/halal_texture.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/halal_texture.jpg COPYONLY)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
)

