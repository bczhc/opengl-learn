//
// Created by bczhc on 8/21/21.
//

#include "shader.h"
#include "lib/io.h"
#include "opengl-lib/error_check.h"

ShaderProgram::ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath) {
    program = compileShaderProgram(
            readFileToString(vertexShaderPath),
            readFileToString(fragmentShaderPath)
    );
}

ShaderProgram::~ShaderProgram() {
    GL_CALL(glDeleteProgram(program))
}

void ShaderProgram::bind() const {
    GL_CALL(glUseProgram(program))
}

void ShaderProgram::unbind() const {
    GL_CALL(glUseProgram(0))
}

ShaderLocation ShaderProgram::findLocation(const char *name) const {
    GL_CALL(i32 location = glGetUniformLocation(program, name))
    if (location == -1) {
        cout << "WARNING: Shader uniform \"" << name << "\" location not found" << endl;
    }
    return ShaderLocation(location);
}

u32 ShaderProgram::compileShader(const char *source, GLenum type) {
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
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

u32 ShaderProgram::compileShaderProgram(const string &vertexShaderSrc, const string &fragmentShaderSrc) {
    u32 program = glCreateProgram();
    u32 vs = compileShader(vertexShaderSrc.c_str(), GL_VERTEX_SHADER);
    u32 fs = compileShader(fragmentShaderSrc.c_str(), GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

u32 ShaderProgram::getProgram() const {
    return program;
}
