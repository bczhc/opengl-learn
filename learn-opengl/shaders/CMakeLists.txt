project(shaders)

add_executable(shaders main.cpp)
target_link_libraries(shaders opengl-lib)
target_compile_definitions(
        shaders PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
)

add_executable(shaders-exercise1 main.cpp)
target_link_libraries(shaders-exercise1 opengl-lib)
target_compile_definitions(
        shaders-exercise1 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/exercise1-vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
)

add_executable(shaders-exercise2 exercise2.cpp)
target_link_libraries(shaders-exercise2 opengl-lib)
target_compile_definitions(
        shaders-exercise2 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/exercise2-vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
)

add_executable(shaders-exercise3 main.cpp)
target_link_libraries(shaders-exercise3 opengl-lib)
target_compile_definitions(
        shaders-exercise3 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/exercise3-vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/exercise3-fragment.glsl"
)
