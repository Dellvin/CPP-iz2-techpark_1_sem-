cmake_minimum_required(VERSION 3.10)
project(Tests)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest)
add_executable(Tests test.cpp)
include_directories(lib/googletest/include)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Tests Threads::Threads)
add_library(staticLib1 STATIC ../libraries/static/IZ2_STATIC.c)
add_library(dynamicLib1 SHARED ../libraries/dynamic/libIZ2_dymamic.c)

target_link_libraries(Tests staticLib1 dynamicLib1)



