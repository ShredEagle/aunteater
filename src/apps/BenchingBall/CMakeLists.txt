project(BenchingBall)


# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
    ComponentPosition.h
    ComponentVelocity.h
    SystemMove.h
    SystemRender.h
    Vec2.h
    globals.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    SystemMove.cpp
    SystemRender.cpp
)

add_executable(${PROJECT_NAME}
    main.cpp
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS})
 
target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}
    aunteater
    ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
)


