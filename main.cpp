#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "def.h"

using namespace std;

#define VERTEX_SHADER_FILE ("/home/bczhc/code/opengl/vertex-shader.glsl")
#define FRAGMENT_SHADER_FILE ("/home/bczhc/code/opengl/fragment-shader.glsl")

string readFileToString(const char *filename) {
    string read;
    FILE *fp = fopen(filename, "rb");
    if (fp == nullptr) {
        cout << "Failed to read file" << endl;
        return read;
    }

    int bufferSize = 4096;
    char buf[bufferSize];
    usize readSize;
    while ((readSize = fread(buf, 1, bufferSize, fp)) != 0) {
        read.append(buf, readSize);
    }
    fclose(fp);

    return read;
}

u32 compileShader(const string &source, GLenum type) {
    u32 shader = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    i32 result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        i32 length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char log[length];
        glGetShaderInfoLog(shader, length, &length, log);
        const char *shaderName;
        switch (type) {
            case GL_VERTEX_SHADER:
                shaderName = "vertex";
                break;
            case GL_FRAGMENT_SHADER:
                shaderName = "fragment";
                break;
            default:
                shaderName = "unknown";
                break;
        }
        cout << shaderName << " shader compilation failed: " << log << endl;
        glDeleteShader(shader);
    }

    return shader;
}

u32 createShader(const string &vertexShaderSrc, const string &fragmentShaderSrc) {
    u32 program = glCreateProgram();
    u32 vs = compileShader(vertexShaderSrc, GL_VERTEX_SHADER);
    u32 fs = compileShader(fragmentShaderSrc, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main() {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit()) {
        cout << "glfwInit() failed" << endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "glewInit() failed" << endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    f32 vertices[6] = {
            -0.5F, -0.5F,
            0.0F, 0.5F,
            0.5F, -0.5F
    };

    u32 buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr);

    u32 shaderProgram = createShader(readFileToString(VERTEX_SHADER_FILE), readFileToString(FRAGMENT_SHADER_FILE));
    glUseProgram(shaderProgram);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}