project(OpenGL_samples VERSION "${CMAKE_PROJECT_VERSION}")

set(${PROJECT_NAME}_HEADERS
    CImg.h
    DrawingPolygons.h
    Globals.h
    ImageReader.h
    Textures.h
)

set(${PROJECT_NAME}_SOURCES
    ImageReader.cpp
)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(JPEG REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad::glad
        glfw
        JPEG::JPEG
)

file(GENERATE OUTPUT $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources/halal_texture.jpg
              INPUT ${CMAKE_SOURCE_DIR}/resources/halal_texture.jpg)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${PROJECT_NAME})
