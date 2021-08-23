project(bilibili-learn)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        bilibili-learn
        main.cpp
        renderer.cpp
        vertex_buffer.cpp
        index_buffer.cpp
        vertex_array.cpp
        texture.cpp
)

target_compile_definitions(
        bilibili-learn PRIVATE
        OPENGL_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/basic.glsl"
        OPENGL_TEXTURE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/texture.png"
)

target_link_libraries(bilibili-learn opengl-lib)