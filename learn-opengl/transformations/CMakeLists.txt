project(transformations)

add_executable(transformations main.cpp)
target_link_libraries(transformations opengl-lib stb_image)
target_compile_definitions(
        transformations PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_MAIN
)

add_executable(transformations-exercise1 main.cpp)
target_link_libraries(transformations-exercise1 opengl-lib stb_image)
target_compile_definitions(
        transformations-exercise1 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_EXERCISE1
)
