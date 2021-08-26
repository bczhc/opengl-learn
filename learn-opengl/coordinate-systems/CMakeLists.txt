project(coordinate-systems)

add_executable(coordinate-systems main.cpp)
target_link_libraries(coordinate-systems opengl-lib stb_image)
target_compile_definitions(
        coordinate-systems PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_MAIN_1
)

add_executable(coordinate-systems2 main2.cpp)
target_link_libraries(coordinate-systems2 opengl-lib stb_image)
target_compile_definitions(
        coordinate-systems2 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex2.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment2.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_MAIN_2
)

add_executable(coordinate-systems3 main2.cpp)
target_link_libraries(coordinate-systems3 opengl-lib stb_image)
target_compile_definitions(
        coordinate-systems3 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex2.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment2.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_MAIN_3
)

add_executable(coordinate-systems-exercise3 main2.cpp)
target_link_libraries(coordinate-systems-exercise3 opengl-lib stb_image)
target_compile_definitions(
        coordinate-systems-exercise3 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex2.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment2.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/../textures/res/face.png"
        CODE_EXERCISE_4
)
