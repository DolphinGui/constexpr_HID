import os

from conans import ConanFile, tools, CMake


class ConstexprHIDConan(ConanFile):
    name = "constexpr_HID"
    version = "0.0.1"
    license = "Unlicense"
    author = "Shin Umeda, umeda.shin@gmail.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "A c++17 library for making HID descriptors"
    topics = ("HID", "c++17", "conan")
    no_copy_source = True
    exports_sources = "include/*", "CMakeLists.txt", "example.cpp"
    requires = "tuplet/1.0.0"
    generators = "cmake_find_package"
    build_requires = "fmt/8.1.1"
    build_policy = "missing"
    
    def build(self): # this is not building a library, just tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
