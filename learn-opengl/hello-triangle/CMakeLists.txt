project(hello-triangle)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello-triangle demo.cpp)
target_link_libraries(hello-triangle GL glfw GLEW lib)

target_compile_definitions(
        hello-triangle PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment.glsl"
)
