import os

from conans import ConanFile, tools


class ConstexprHIDConan(ConanFile):
    name = "constexpr_HID"
    version = "0.0.1"
    license = "Unlicense"
    author = "Shin Umeda, umeda.shin@gmail.com"
    url = "<Package recipe repository url here, for issues about the package>"
    description = "A c++17 library for making HID descriptors"
    topics = ("HID", "c++17", "conan")
    no_copy_source = True
    exports_sources = "include/*"

    def package(self):
        self.copy("*.hpp")

    def package_id(self):
        self.info.header_only()
