//
// Created by bczhc on 8/23/21.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include "lib/types.h"
#include "lib/io.h"

using namespace std;

u32 compileProgram() {
    const string &vertexShaderSrc = readFileToString(VERTEX_SHADER_FILE_PATH);
    const string &fragmentShaderSrc = readFileToString(FRAGMENT_SHADER_FILE_PATH);
    const char *vss = vertexShaderSrc.c_str();
    const char *fss = fragmentShaderSrc.c_str();

    u32 program = glCreateProgram();

    u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vss, nullptr);
    glShaderSource(fragmentShader, 1, &fss, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

int main() {
    if (glfwInit() == -1) {
        cout << "glfwInit() failed" << endl;
        abort();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(500, 500, "Window", nullptr, nullptr);
    if (window == nullptr) {
        cout << "glfwCreateWindow(...) failed" << endl;
        glfwTerminate();
        abort();
    }

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        cout << "glewInit() failed" << endl;
        abort();
    }

    f32 buffers[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0.5F, 0.5F,
            -0.5F, 0.5F,
    };

    u32 indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    u32 va;
    glCreateVertexArrays(1, &va);
    u32 vb;
    glCreateBuffers(1, &vb);
    u32 ib;
    glCreateBuffers(1, &ib);

    glBindVertexArray(va);

    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffers), buffers, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    u32 program = compileProgram();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(va);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &ib);
    glDeleteBuffers(1, &vb);
    glDeleteVertexArrays(1, &va);
    glDeleteProgram(program);
    glfwTerminate();
    return 0;
}