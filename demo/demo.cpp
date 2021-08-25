//
// Created by bczhc on 8/25/21.
//

#include <opengl-lib/lib.h>
#include <opengl-lib/shader.h>
#include <opengl-lib/error_check.h>

void opengl_operation(GLFWwindow *window) {
    ShaderProgram program(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH);
    const ShaderLocation &markLocation = program.findLocation("mark");
    f32 buffer[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0.0F, 0.5F,
            -1.0F, 0.0F,
            1.0F, 0.0F
    };
    u32 vb;
    u32 va;
    GL_CALL(glGenBuffers(1, &vb))
    GL_CALL(glGenVertexArrays(1, &va))

    GL_CALL(glBindVertexArray(va))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb))
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW))

    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(f32), nullptr))
    GL_CALL(glEnableVertexAttribArray(0))

    GL_CALL(glBindVertexArray(0))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program.bind();
        markLocation.setUniform(false);
        GL_CALL(glBindVertexArray(va))
        GL_CALL(glDrawArrays(GL_POINTS, 0, 1))
//        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3))
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3))
        markLocation.setUniform(true);
        GL_CALL(glDrawArrays(GL_LINES, 3, 2))

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    GL_CALL(glDeleteVertexArrays(1, &va))
    GL_CALL(glDeleteBuffers(1, &vb))
}

int main() {
    GLFWwindow *window = opengl_lib::initAndCreateWindow(500, 500, "Window");
    opengl_lib::setAutoViewportWhenWindowSizeChanged(window);

    opengl_operation(window);

    glfwTerminate();
    return 0;
}