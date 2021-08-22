//
// Created by bczhc on 8/22/21.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include "lib/types.h"
#include "lib/io.h"
#include <iostream>
#include "lib/gl_error_check.h"

using namespace std;

struct ShaderProgramSource {
    string vertex;
    string fragment;
};

ShaderProgramSource readShaderProgramSource() {
    return {
            readFileToString(VERTEX_SHADER_FILE_PATH),
            readFileToString(FRAGMENT_SHADER_FILE_PATH)
    };
}

u32 compileShader(const string &source, GLenum type) {
    u32 shader = glCreateShader(type);
    const char *str = source.c_str();
    glShaderSource(shader, 1, &str, nullptr);
    glCompileShader(shader);
    return shader;
}

u32 compileProgram() {
    const ShaderProgramSource &source = readShaderProgramSource();
    u32 vertexShader = compileShader(source.vertex, GL_VERTEX_SHADER);
    u32 fragmentShader = compileShader(source.fragment, GL_FRAGMENT_SHADER);
    u32 program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

void frameBufferSizeCallback(GLFWwindow *, i32 width, i32 height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (glfwInit() == -1) {
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(500, 500, "Window", nullptr, nullptr);
    if (window == nullptr) {
        glfwTerminate();
        abort();
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        abort();
    }

    cout << glGetString(GL_VERSION) << endl;

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    f32 buffer[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0.0F, 0.5F
    };

    GL_CALL(u32 va)
    GL_CALL(glGenVertexArrays(1, &va))
    GL_CALL(u32 vb)
    GL_CALL(glGenBuffers(1, &vb))

    GL_CALL(glBindVertexArray(va))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb))
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW))

    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr))
    GL_CALL(glEnableVertexAttribArray(0))

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
    GL_CALL(glBindVertexArray(0))

    GL_CALL(u32 program = compileProgram())

    while (!glfwWindowShouldClose(window)) {
        GL_CALL(glClearColor(0.2F, 0.3F, 0.3F, 1.0F))
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT))

        GL_CALL(glUseProgram(program))
        GL_CALL(glBindVertexArray(va))
        GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 3))

        GL_CALL(glfwSwapBuffers(window))
        GL_CALL(glfwPollEvents())
    }

    glDeleteVertexArrays(1, &va);
    glDeleteBuffers(1, &vb);
    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}
