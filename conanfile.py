from conans import ConanFile, tools, CMake

class MatPlotLibCppConan(ConanFile):
    name = "matplotlibcpp17"
    branch = "master"
    tag = "1.0.1"
    version = tag
    settings = "os", "compiler", "build_type", "arch"
    requires = ["pybind11/2.4.3"]
    generators = ["cmake", "cmake_find_package"]
    exports_sources = "*"

    #def source(self):
        #git = tools.Git(folder="matplotlipcpp17")
        #git.clone("https://github.com/soblin/matplotlibcpp17.git", self.branch)
        #git.checkout(self.tag)

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["ADD_DEMO"] = "OFF"
        cmake.definitions["DO_TEST"] = "OFF"
        #cmake.configure(source_folder="matplotlibcpp17")
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()
