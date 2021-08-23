//
// Created by bczhc on 8/21/21.
//

#include "shader.h"
#include "lib/io.h"
#include "opengl-lib/error_check.h"

Shader::Shader(const char *filepath) {
    const Shader::ShaderSource &source = parseShaderSource(filepath);
    program = compileShaderProgram(source.vertex, source.fragment);
}

Shader::~Shader() {
    GL_CALL(glDeleteProgram(program))
}

void Shader::bind() const {
    GL_CALL(glUseProgram(program))
}

void Shader::unbind() const {
    GL_CALL(glUseProgram(0))
}

ShaderLocation Shader::findLocation(const char *name) const {
    GL_CALL(i32 location = glGetUniformLocation(program, name))
    if (location == -1) {
        cout << "WARNING: Shader uniform \"" << name << "\" location not found" << endl;
    }
    return ShaderLocation(location);
}

Shader::ShaderSource Shader::parseShaderSource(const char *path) {
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

u32 Shader::compileShader(const string &source, GLenum type) {
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

u32 Shader::compileShaderProgram(const string &vertexShaderSrc, const string &fragmentShaderSrc) {
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
