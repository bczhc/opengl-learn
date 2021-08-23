cmake_minimum_required(VERSION 3.16)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_subdirectory(lib)
add_subdirectory(bilibili-learn)
add_subdirectory(learn-opengl/hello-triangle)
