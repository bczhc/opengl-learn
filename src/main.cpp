#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "def.h"
#include "exception.h"
#include "option.hpp"
#include <cstdlib>
#include <cassert>

using namespace std;

#define SHADER_FILE_PATH ("/home/bczhc/code/opengl/res/basic.glsl")

#define GL_CALL(x) glClearError(); \
    x;                            \
    if (glCheckError()) {          \
        cout << #x << __FILE__ << ' ' << __LINE__ << endl; \
        abort();                   \
    }

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glCheckError() {
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        cout << "[OpenGL Error] (" << error << ") ";
        return true;
    }
    return false;
}

enum ShaderType {
    UNKNOWN,
    VERTEX,
    FRAGMENT
};

struct ShaderSource {
    string vertex;
    string fragment;
};

Option<string> readLine(FILE *fp) {
    bool eof = true;
    string line;
    char c;
    while (fread(&c, 1, 1, fp) != 0) {
        eof = false;
        if (c == '\n') {
            break;
        }
        line.push_back(c);
    }
    if (eof) return Option<string>::getNone();
    return Option(line);
}

ShaderSource parseShaderSource(const char *path) {
    FILE *fp = fopen(path, "rb");
    if (fp == nullptr) {
        throw IOException("Failed to open shader file");
    }

    string vertexSrc, fragmentSrc;
    ShaderType type = ShaderType::UNKNOWN;
    bool shaderMarkLine = false;
    while (true) {
        const Option<string> &option = readLine(fp);
        if (option.isNone()) {
            break;
        }
        auto line = option.get();

        if (line.starts_with("#shader vertex")) {
            type = ShaderType::VERTEX;
            shaderMarkLine = true;
        }
        if (line.starts_with("#shader fragment")) {
            type = ShaderType::FRAGMENT;
            shaderMarkLine = true;
        }

        if (shaderMarkLine) {
            shaderMarkLine = false;
            continue;
        }
        switch (type) {
            case VERTEX:
                vertexSrc.append(line).push_back('\n');
                break;
            case FRAGMENT:
                fragmentSrc.append(line).push_back('\n');
                break;
            default:
                break;
        }
    }
    fclose(fp);
    return {
            .vertex = vertexSrc,
            .fragment = fragmentSrc
    };
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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        cout << "glfwCreateWindow(...) failed" << endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        cout << "glewInit() failed" << endl;
        return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    glfwSwapInterval(1);

    f32 vertices[] = {
            -0.5F, -0.5F, // 0
            0.5F, -0.5F, // 1
            0.5F, 0.5F, // 2
            -0.5F, 0.5F, // 3
    };

    GLuint vertexIndices[] = {
            0, 1, 2,
            2, 3, 0
    };

    u32 vao;
    GL_CALL(glGenVertexArrays(1, &vao))
    GL_CALL(glBindVertexArray(vao))

    u32 buffer;
    GL_CALL(glGenBuffers(1, &buffer))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, buffer))
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW))

    GL_CALL(glEnableVertexAttribArray(0))
    GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32), nullptr))

    u32 ibo;
    GL_CALL(glGenBuffers(1, &ibo))
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo))
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndices), vertexIndices, GL_STATIC_DRAW))

    GL_CALL(const ShaderSource &shaderSource = parseShaderSource(SHADER_FILE_PATH))
    GL_CALL(u32 shaderProgram = createShader(shaderSource.vertex, shaderSource.fragment))
    GL_CALL(glUseProgram(shaderProgram))

    GL_CALL(GLint location = glGetUniformLocation(shaderProgram, "u_Color"))
    assert(location != -1);

    GL_CALL(glBindVertexArray(0))
    GL_CALL(glUseProgram(0))
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))

    f32 r = 0;
    f32 increment = 0.05;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (r > 1.0) {
            increment = -0.05;
        } else if (r < 0.0) {
            increment = 0.05;
        }
        r += increment;

        GL_CALL(glUseProgram(shaderProgram))
        GL_CALL(glUniform4f(location, r, 0.3F, 0.8F, 1.0F))
        GL_CALL(glBindVertexArray(vao))
        // also works without the ibo binding
//        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo))
        GL_CALL(glDrawElements(GL_TRIANGLES, sizeof(vertexIndices) / sizeof(vertexIndices[0]), GL_UNSIGNED_INT,
                               nullptr))

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}