project(textures)

add_executable(textures main.cpp)
target_link_libraries(textures opengl-lib stb_image)
target_compile_definitions(
        textures PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/wall.jpg"
)
