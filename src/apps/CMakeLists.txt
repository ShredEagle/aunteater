conditional_add_subdirectory(TestSuite DEPENDS Cpputest VERBOSE)
conditional_add_subdirectory(BenchingBall DEPENDS GLFW OpenGL VERBOSE)
conditional_add_subdirectory(OpenGL DEPENDS GLFW OpenGL VERBOSE)

