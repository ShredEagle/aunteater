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

find_package(glad REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_compile_definitions(${PROJECT_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif()

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ad::aunteater
        glad::glad
        glfw
)

set_target_properties(${PROJECT_NAME} PROPERTIES
                      VERSION "${${PROJECT_NAME}_VERSION}"
)


##
## Install
##

install(TARGETS ${PROJECT_NAME})
