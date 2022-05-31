from conans import ConanFile, tools
from conan.tools.cmake import CMake
from conan.tools.files import copy

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

    requires = ("boost/1.79.0",)

    build_policy = "missing"
    generators = "CMakeDeps", "CMakeToolchain"

    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto",
        "submodule": "recursive",
    }

    python_requires="shred_conan_base/0.0.2@adnn/develop"
    python_requires_extend="shred_conan_base.ShredBaseConanFile"


    def configure(self):
        tools.check_min_cppstd(self, "17")


    def requirements(self):
        if self.options.build_tests:
           self.requires("glad/0.1.34")
           self.requires("glfw/3.3.6")
           self.requires("libjpeg/9d")

           self.options["glad"].gl_version = "4.1"


    def _generate_cmake_configfile(self):
        """ Generates a conanuser_config.cmake file which includes the file generated by """
        """ cmake_paths generator, and forward the remaining options to CMake. """
        with open("conanuser_config.cmake", "w") as config:
            config.write("message(STATUS \"Including user generated conan config.\")\n")
            # avoid path.join, on Windows it outputs '\', which is a string escape sequence.
            #config.write("include(\"{}\")\n".format("${CMAKE_CURRENT_LIST_DIR}/conan_paths.cmake"))
            config.write("set({} {})\n".format("BUILD_tests", self.options.build_tests))
            config.write("set(CMAKE_EXPORT_COMPILE_COMMANDS 1)\n".format("BUILD_tests", self.options.build_tests))

    def export_sources(self):
        # The path of the CMakeLists.txt we want to export is one level above
        folder = path.join(self.recipe_folder, "..")
        copy(self, "*.txt", folder, self.export_sources_folder)


    def generate(self):
        self._generate_cmake_configfile()


    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake


    def build(self):
        cmake = self._configure_cmake()
        cmake.build()


    def package(self):
        cmake = self._configure_cmake()
        cmake.install()


    def package_info(self):
        #self.cpp_info.libs = tools.collect_libs(self)
        self.cpp_info.set_property("cmake_find_mode", "none")
        if self.folders.build_folder:
            self.cpp_info.builddirs.append(self.folders.build_folder)
        else:
            self.cpp_info.builddirs.append(path.join('lib', 'cmake'))
