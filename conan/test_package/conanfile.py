import os

from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain


class AunteaterTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_paths", "cmake_find_package", "CMakeToolchain"

    build_requires = "cmake/3.20.4"


    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["CMAKE_PROJECT_PackageTest_INCLUDE"] = "${CMAKE_BINARY_DIR}/conan_paths.cmake"
        tc.generate()


    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()


    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')


    def test(self):
        if not tools.cross_building(self.settings):
            self.run(".%sexample" % os.sep)
