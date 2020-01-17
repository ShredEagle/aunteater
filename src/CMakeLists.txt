add_subdirectory(libs/aunteater/aunteater)

option(BUILD_tests "Build the test applications" ON)
if(BUILD_tests)
    add_subdirectory(apps/TestSuite)
    add_subdirectory(apps/BenchingBall)
    add_subdirectory(apps/OpenGL)
endif()
