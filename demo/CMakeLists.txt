project(demo)

add_executable(demo demo.cpp)
target_link_libraries(demo opengl-lib)
target_compile_definitions(
        demo PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
)
