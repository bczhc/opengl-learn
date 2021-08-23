//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "shader_location.h"
#include <string>

#include <GL/glew.h>

using namespace std;

class ShaderProgram {
private:
    u32 program;
public:
    explicit ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);

    ~ShaderProgram();

    void bind() const;

    void unbind() const;

    ShaderLocation findLocation(const char *name) const;

private:
    struct ShaderSource {
        string vertex;
        string fragment;
    };

    static u32 compileShader(const char* source, GLenum type);

    static u32 compileShaderProgram(const string &vertexShaderSrc, const string &fragmentShaderSrc);
};

#endif //OPENGL_SHADER_H
