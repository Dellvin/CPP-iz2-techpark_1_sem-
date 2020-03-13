cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
add_executable(Tests test.cpp)
target_include_directories(Tests PRIVATE ../src)
target_link_libraries(Tests gtest gmock gtest_main)
