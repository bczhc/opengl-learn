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

u32 compileProgram(const char *vertexShaderSrc, const char *fragmentShaderSrc) {
    u32 program = glCreateProgram();

    u32 vertexShader = glCreateShader(GL_VERTEX_SHADER);
    u32 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

u32 compileProgramFromFile(const char *vertexShaderPath, const char *fragmentShaderPath) {
    const string &vRead = readFileToString(vertexShaderPath);
    const string &fRead = readFileToString(fragmentShaderPath);
    const char *vCStr = vRead.c_str();
    const char *fCStr = fRead.c_str();

    return compileProgram(vCStr, fCStr);
}

struct Programs {
    u32 program1;
    u32 program2;
};

Programs compilePrograms() {
    return {
            compileProgramFromFile(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH),
            compileProgramFromFile(VERTEX_SHADER_FILE_PATH, FRAGMENT2_SHADER_FILE_PATH)
    };
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

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *, i32 width, i32 height) {
        glViewport(0, 0, width, height);
    });

    f32 triangleBuffer[] = {
            -0.5F, -0.5F,
            0.5F, -0.5F,
            0.5F, 0.5F,
            0.5F, 0.5F,
            -0.5F, 0.5F,
            -0.5F, -0.5F
    };

    u32 vbs[2];
    glCreateBuffers(2, vbs);
    u32 vas[2];
    glCreateVertexArrays(2, vas);

    glBindVertexArray(vas[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbs[0]);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(f32), triangleBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(vas[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbs[1]);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(f32), triangleBuffer + 6, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    auto programs = compilePrograms();

    bool mark = false;

    glfwSwapInterval(5);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        mark = !mark;

        glUseProgram(mark ? programs.program1 : programs.program2);
        glBindVertexArray(vas[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(mark ? programs.program2 : programs.program1);
        glBindVertexArray(vas[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(2, vbs);
    glDeleteVertexArrays(2, vas);
    glDeleteProgram(programs.program1);
    glDeleteProgram(programs.program2);
    glfwTerminate();
    return 0;
}
