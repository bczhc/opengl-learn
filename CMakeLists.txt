cmake_minimum_required(VERSION 3.19)
project(opengl)

add_compile_definitions(
        OPENGL_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/basic.glsl"
        OPENGL_TEXTURE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/png"
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/lib)

add_executable(
        main
        src/main.cpp
        src/renderer.cpp
        src/vertex_buffer.cpp
        src/index_buffer.cpp
        src/vertex_array.cpp
        src/shader.cpp
        src/shader_location.cpp
        src/texture.cpp
)

target_link_libraries(main glfw GL GLEW lib)

add_subdirectory(src/learn-opengl/hello-triangle)
