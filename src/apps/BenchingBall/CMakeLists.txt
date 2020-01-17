project(BenchingBall VERSION "${CMAKE_PROJECT_VERSION}")

set(${PROJECT_NAME}_HEADERS
    ComponentPosition.h
    ComponentVelocity.h
    SystemMove.h
    SystemRender.h
    Vec2.h
    globals.h
)

set(${PROJECT_NAME}_SOURCES
    SystemMove.cpp
    SystemRender.cpp
)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ad::aunteater
        glfw
        OpenGL::GL
)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${PROJECT_NAME})
