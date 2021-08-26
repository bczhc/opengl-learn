//
// Created by bczhc on 8/26/21.
//


#include <opengl-lib/lib.h>
#include <opengl-lib/shader.h>
#include <third_party/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define WIDTH (800.0F)
#define HEIGHT (600.0F)

static f32 whAspect = WIDTH / HEIGHT;

// coordinate (3) | texture coordinate (2)
static f32 buffer[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

u32 openTexture(const char *path, u32 slot) {
    stbi_set_flip_vertically_on_load(1);
    i32 width, height, p;
    auto data = stbi_load(path, &width, &height, &p, STBI_rgb_alpha);

    u32 texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return texture;
}

void openglOperation(GLFWwindow *window) {
    u32 vb;
    glGenBuffers(1, &vb);
    u32 va;
    glGenVertexArrays(1, &va);

    glBindVertexArray(va);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (const void *) (3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderProgram program(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH);
    program.bind();

    program.findLocation("texture1").setUniform(0);
    program.findLocation("texture2").setUniform(1);
    const struct {
        ShaderLocation model;
        ShaderLocation view;
        ShaderLocation projection;
    } shaderTransformation{
            program.findLocation("model"),
            program.findLocation("view"),
            program.findLocation("projection")
    };

    u32 texture0 = openTexture(TEXTURE_IMAGE_FILE_PATH, 0);
    u32 texture1 = openTexture(TEXTURE_IMAGE2_FILE_PATH, 1);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0F), whAspect, 0.1F, 100.0F);
    glm::mat4 viewMatrix = glm::mat4(1.0F);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0F, 0.0F, -3.0F));
    shaderTransformation.projection.setUniformMatrix(glm::value_ptr(projectionMatrix));
    shaderTransformation.view.setUniformMatrix(glm::value_ptr(viewMatrix));

    glEnable(GL_DEPTH_TEST);

#ifdef CODE_MAIN_3
    glm::vec3 modelTranslations[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };
#endif

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.bind();
        glBindVertexArray(va);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1);

#ifdef CODE_MAIN_2
        glm::mat4 modelMatrix = glm::mat4(1.0F);
        modelMatrix = glm::rotate(modelMatrix, (f32) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        shaderTransformation.model.setUniformMatrix(glm::value_ptr(modelMatrix));

        glDrawArrays(GL_TRIANGLES, 0, 36);
#elif defined(CODE_MAIN_3)
        for (u32 i = 0; i < 10; ++i) {
                auto translation = modelTranslations[i];
                glm::mat4 modelMatrix = glm::mat4(1.0F);
                modelMatrix = glm::translate(modelMatrix, translation);
                modelMatrix = glm::rotate(
                        modelMatrix, (f32) glfwGetTime() + glm::radians(50.0F * (f32) i),
                        glm::vec3(rand(), rand(), rand())
                );
                shaderTransformation.model.setUniformMatrix(glm::value_ptr(modelMatrix));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
#elif defined(CODE_EXERCISE_4)

#else
#error missing learning phase (chapter) definition
#endif


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vb);
    glDeleteVertexArrays(1, &va);
    glDeleteTextures(1, &texture0);
    glDeleteTextures(1, &texture1);
}

int main() {
    auto window = opengl_lib::initAndCreateWindow(WIDTH, HEIGHT, "Window");
    opengl_lib::setAutoViewportWhenWindowSizeChanged(window);
    opengl_lib::setQuitWhenKeyListened(window);

    openglOperation(window);

    glfwTerminate();
    return 0;
}