from conans import ConanFile, CMake, tools

from os import path


class AunteaterConan(ConanFile):
    """ Conan recipe for Aunteater """

    name = "aunteater"
    license = "MIT"
    url = "https://github.com/Adnn/aunteater"
    description = "Aunteater framework for Entity Component Family System"
    topics = ("game", "framework", "ecs")
    settings = (
        "os", # Naturally forwarded for native compilation
        "compiler", # Build-helper sets -> CONAN_COMPILER
                    # Need to check it manually in CMake scripts (check_compiler_version)
                    # * compiler.cppstd -> CONAN_CMAKE_CXX_STANDARD & CONAN_CMAKE_CXX_EXTENSIONS (standard with "gnu" prefix, e.g. "gnu14")
                    #   Need to map it manually to CMAKE_CXX_STANDARD && CMAKE_CXX_EXTENSIONS (conan_set_std)
                    # * compiler.libcxx -> CONAN_LIBCXX
                    #   Need to map it manually to compiler dependent flags (conan_set_libcxx)
                    # * compiler.runtime -> CONAN_LINK_RUNTIME
                    #   Need to manually alter the compilation flags (conan_set_vs_runtime)
        "build_type", # Buildhelper auto sets CMake var CMAKE_BUILD_TYPE
                      # All that is needed
        "arch") # Naturally forwarded for native compilation
    options = {
        "shared": [True, False], # Buildhelper auto sets CMake var BUILD_SHARED_LIBS
                                 # All that is needed
        "build_tests": [True, False], # Need to manually map to CMake var BUILD_tests
    }
    default_options = {
        "shared": False,
        "build_tests": False,
    }

    requires = ("boost/1.71.0@conan/stable",)

    build_requires = ("cmake_installer/[>=3.16]@conan/stable",)

    build_policy = "missing"
    generators = "cmake_paths", "cmake"

    scm = {
        "type": "git",
        "subfolder": "cloned_repo",
        "url": "auto",
        "revision": "auto",
        "submodule": "recursive",
    }


    def requirements(self):
        if self.options.build_tests:
           self.requires("glad/0.1.29@bincrafters/stable")
           self.requires("glfw/3.3@bincrafters/stable")
           self.requires("libjpeg/9c@bincrafters/stable")

           self.options["glad"].api_version = "3.3"


    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["CMAKE_PROJECT_Aunteater_INCLUDE"] = \
            path.join(self.source_folder, "cloned_repo", "cmake", "conan", "customconan.cmake")
        cmake.definitions["BUILD_tests"] = self.options.build_tests
        cmake.configure(source_folder="cloned_repo")
        return cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
