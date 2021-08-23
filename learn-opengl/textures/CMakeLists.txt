project(textures)

add_executable(textures-triangle triangle.cpp)
target_link_libraries(textures-triangle opengl-lib stb_image)
target_compile_definitions(
        textures-triangle PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/wall.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/res/face.png"
)

add_executable(textures main.cpp)
target_link_libraries(textures opengl-lib stb_image)
target_compile_definitions(
        textures PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/res/face.png"
)

add_executable(textures-exercise1 main.cpp)
target_link_libraries(textures-exercise1 opengl-lib stb_image)
target_compile_definitions(
        textures-exercise1 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment-exercise1.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/res/face.png"
)

add_executable(textures-exercise4 exercise4.cpp)
target_link_libraries(textures-exercise4 opengl-lib stb_image)
target_compile_definitions(
        textures-exercise4 PRIVATE
        VERTEX_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/vertex.glsl"
        FRAGMENT_SHADER_FILE_PATH="${PROJECT_SOURCE_DIR}/shaders/fragment-exercise4.glsl"
        TEXTURE_IMAGE_FILE_PATH="${PROJECT_SOURCE_DIR}/res/container.jpg"
        TEXTURE_IMAGE2_FILE_PATH="${PROJECT_SOURCE_DIR}/res/face.png"
)
