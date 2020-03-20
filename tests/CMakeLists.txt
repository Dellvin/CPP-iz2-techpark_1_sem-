cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(./lib/googletest)
add_executable(Tests test.cpp)
include_directories(lib/googletest/include)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#add_library(staticLib STATIC ../libraries/static/IZ2_STATIC.c ../libraries/static/IZ2_STATIC.h)
#add_library(dynamicLib SHARED ../libraries/dynamic/libIZ2_dymamic.c ../libraries/dynamic/libIZ2_dymamic.h)

#target_include_directories(staticLib1 PUBLIC ../libraries/static)
#target_include_directories(dynamicLib1 PUBLIC ../libraries/dynamic)

target_link_libraries(Tests staticLib dynamicLib gtest gmock gtest_main)

