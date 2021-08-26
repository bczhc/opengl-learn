cmake_minimum_required(VERSION 3.16)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(third_party/stb_image)
include_directories(third_party/glm-headers)

add_subdirectory(lib)
add_subdirectory(opengl-lib)
add_subdirectory(bilibili-learn)
add_subdirectory(learn-opengl)
add_subdirectory(third_party)
add_subdirectory(demo)
