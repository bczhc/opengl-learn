project(hello-triangle)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello-triangle demo.cpp)
target_link_libraries(hello-triangle GL glfw GLEW lib)
