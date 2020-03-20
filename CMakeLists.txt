cmake_minimum_required(VERSION 3.10)
project(iz2 C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic")

add_executable(iz2 main.c)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(iz2 Threads::Threads)
add_library(staticLib STATIC ./libraries/static/IZ2_STATIC.c)
add_library(dynamicLib SHARED ./libraries/dynamic/libIZ2_dymamic.c)


target_link_libraries(dynamicLib -lpthread)
target_link_libraries(iz2 staticLib dynamicLib)

add_subdirectory(tests)

