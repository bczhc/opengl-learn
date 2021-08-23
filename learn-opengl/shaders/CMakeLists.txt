project(shaders)

add_executable(shaders main.cpp)
target_link_libraries(shaders opengl-lib)

target_compile_definitions(
        shaders PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
)
