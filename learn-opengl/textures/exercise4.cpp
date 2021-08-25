//
// Created by bczhc on 8/23/21.
//

#include "opengl-lib/lib.h"
#include "opengl-lib/shader.h"
#include "third_party/stb_image.h"

static f32 gMixRatio = 0.0;

void keyCallback(GLFWwindow*, i32 key, i32, i32, i32) {
    if (key == GLFW_KEY_UP && gMixRatio < 1.0F) {
        gMixRatio += 0.01F;
    } else if (key == GLFW_KEY_DOWN && gMixRatio > 0.0F) {
        gMixRatio -= 0.01F;
    }
}

class TextureImage {
public:
    i32 width{}, height{}, channel{};
    u8 *data{};

    explicit TextureImage(const char *path) {
        stbi_set_flip_vertically_on_load(1);
        data = stbi_load(path, &width, &height, &channel, STBI_rgb_alpha);
    }

    ~TextureImage() {
        stbi_image_free(data);
    }
};

int main() {
    GLFWwindow *window = opengl_lib::initAndCreateWindow(500, 500, "Window");

    opengl_lib::setAutoViewportWhenWindowSizeChanged(window);
    glfwSetKeyCallback(window, keyCallback);

    f32 buffer[] = {
            // position (2) | color (3) | texture coordinate (2) | texture2 coordinate (2)
            -0.5F, -0.5F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F,
            0.5F, -0.5F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F,
            0.5F, 0.5F, 1.0F, 0.0F, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F,
            -0.5F, 0.5F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F
    };

    u32 indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    u32 vb;
    glGenBuffers(1, &vb);
    u32 va;
    glGenVertexArrays(1, &va);
    u32 ib;
    glGenBuffers(1, &ib);

    glBindVertexArray(va);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    i32 strip = sizeof(buffer) / 4;
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, strip, nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, strip, (const void *) (2 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, strip, (const void *) (5 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, strip, (const void *) (7 * sizeof(f32)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    TextureImage image(TEXTURE_IMAGE_FILE_PATH);
    u32 texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    TextureImage image2(TEXTURE_IMAGE2_FILE_PATH);
    u32 texture2;
    glGenTextures(1, &texture2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image2.width, image2.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    auto program = new ShaderProgram(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH);
    program->bind();
    const ShaderLocation &shaderTextureSampler = program->findLocation("texture_sampler");
    const ShaderLocation &shaderTexture2Sampler = program->findLocation("texture2_sampler");
    const ShaderLocation &shaderMixRatio = program->findLocation("mix_ratio");
    shaderTextureSampler.setUniform(0);
    shaderTexture2Sampler.setUniform(1);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program->bind();
        shaderMixRatio.setUniform(gMixRatio);

        glBindVertexArray(va);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, nullptr);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &va);
    glDeleteBuffers(1, &vb);
    delete program;
    glfwTerminate();
    return 0;
}
