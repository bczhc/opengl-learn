project(opengl-lib)

add_library(
        opengl-lib SHARED
        lib.cpp
        error_check.cpp
        shader.cpp
        shader_location.cpp
)
target_link_libraries(opengl-lib GL GLEW glfw lib)
