add_subdirectory(libs/aunteater/aunteater)

option(BUILD_tests "Build the test applications" ON)
if(BUILD_tests)
    add_subdirectory(apps/TestSuite)
    #conditional_add_subdirectory(BenchingBall DEPENDS GLFW OpenGL VERBOSE)
    #conditional_add_subdirectory(OpenGL DEPENDS GLFW OpenGL JPEG VERBOSE)
endif()
