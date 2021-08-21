//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "shader_location.h"
#include <string>
#include "renderer.h"

using namespace std;

class Shader {
private:
    u32 program;
public:
    explicit Shader(const char *filepath);

    ~Shader();

    void bind() const;

    void unbind() const;

    ShaderLocation findLocation(const char *name) const;

private:
    enum ShaderType {
        UNKNOWN,
        VERTEX,
        FRAGMENT
    };

    struct ShaderSource {
        string vertex;
        string fragment;
    };

    static ShaderSource parseShaderSource(const char *path);

    static u32 compileShader(const string &source, GLenum type);

    static u32 compileShaderProgram(const string &vertexShaderSrc, const string &fragmentShaderSrc);
};

#endif //OPENGL_SHADER_H
