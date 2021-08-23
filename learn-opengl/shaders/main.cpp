//
// Created by bczhc on 8/23/21.
//

#include "opengl-lib/lib.h"
#include "opengl-lib/shader.h"

using namespace std;

static f32 buffer[] = {
        -0.5F, -0.5F, 1.0F, 0.0F, 0.0F,
        0.5F, -0.5F, 0.0F, 1.0F, 0.0F,
        0.0F, 0.5F, 0.0F, 0.0F, 1.0F
};

void openglOperations(GLFWwindow *window) {
    u32 vb;
    glGenBuffers(1, &vb);
    u32 va;
    glGenVertexArrays(1, &va);

    glBindVertexArray(va);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 5 * sizeof(f32), (const void *) (2 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(va);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ShaderProgram program(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program.bind();
        glBindVertexArray(va);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        program.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    auto window = opengl_lib::initAndCreateWindow(500, 500, "Window");

    opengl_lib::setAutoViewportWhenWindowSizeChanged(window);

    openglOperations(window);

    glfwTerminate();
}
