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
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        OPENGL_TEXTURE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/texture.png"
)

target_link_libraries(bilibili-learn opengl-lib stb_image)