project(hello-triangle)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello-triangle main.cpp)
target_link_libraries(hello-triangle opengl-lib)

add_executable(hello-triangle-exercise1 exercise1.cpp)
target_link_libraries(hello-triangle-exercise1 opengl-lib)

add_executable(hello-triangle-exercise2 exercise2.cpp)
target_link_libraries(hello-triangle-exercise2 opengl-lib)

add_executable(hello-triangle-exercise3 exercise3.cpp)
target_link_libraries(hello-triangle-exercise3 opengl-lib)

target_compile_definitions(
        hello-triangle PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment.glsl"
)
target_compile_definitions(
        hello-triangle-exercise1 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment.glsl"
)
target_compile_definitions(
        hello-triangle-exercise2 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment.glsl"
)
target_compile_definitions(
        hello-triangle-exercise3 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment.glsl"
        FRAGMENT2_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/res/fragment2.glsl"
)
