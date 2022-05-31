import os

from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain


class AunteaterTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"


    def generate(self):
        tc = CMakeToolchain(self)
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
