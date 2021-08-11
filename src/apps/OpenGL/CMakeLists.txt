set(TARGET_NAME OpenGL_samples)

set(${TARGET_NAME}_HEADERS
    CImg.h
    DrawingPolygons.h
    Globals.h
    ImageReader.h
    Textures.h
)

set(${TARGET_NAME}_SOURCES
    ImageReader.cpp
)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(JPEG REQUIRED)

add_executable(${TARGET_NAME}
    main.cpp
    ${${TARGET_NAME}_SOURCES}
    ${${TARGET_NAME}_HEADERS})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${TARGET_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()

target_link_libraries(${TARGET_NAME}
    PRIVATE
        glad::glad
        glfw
        JPEG::JPEG
)

file(GENERATE OUTPUT $<TARGET_FILE_DIR:${TARGET_NAME}>/resources/halal_texture.jpg
              INPUT ${PROJECT_SOURCE_DIR}/resources/halal_texture.jpg)

set_target_properties(${TARGET_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${TARGET_NAME})
