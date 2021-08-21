cmake_minimum_required(VERSION 3.19)
project(opengl)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo src/main.cpp src/exception.cpp)

target_link_libraries(demo glfw GL GLEW)