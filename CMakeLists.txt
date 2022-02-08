cmake_minimum_required(VERSION 3.12)

project(constexpr_HID_tests CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(example1 examples/example1.cpp)
target_include_directories(example1 PRIVATE include)

set_property(TARGET example1 PROPERTY CXX_STANDARD 20)

find_package(fmt REQUIRED)
target_link_libraries(example1 fmt::fmt)
find_package(tuplet REQUIRED)
target_link_libraries(example1 tuplet::tuplet)
enable_testing()
add_test(NAME example1
         COMMAND example1)