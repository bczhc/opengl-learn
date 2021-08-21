//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/glew.h>
#include <iostream>
#include "def.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"

using namespace std;

#define GL_CALL(x) glClearError(); \
    x;                            \
    if (glCheckError(__FILE__, __LINE__, #x)) {          \
        abort();                   \
    }

void glClearError();

void glLogError(GLenum error, const char *file, u32 line, const char *lineCode);

bool glCheckError(const char *file, u32 line, const char *lineCode);

class Renderer {
public:
    void draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;

    void clear() const;
};

#endif //OPENGL_RENDERER_H
