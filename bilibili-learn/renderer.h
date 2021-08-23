//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <GL/glew.h>
#include <iostream>
#include "lib/types.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "opengl-lib/shader.h"
#include "opengl-lib/error_check.h"

using namespace std;

class Renderer {
public:
    void draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &shader) const;

    void clear() const;
};

#endif //OPENGL_RENDERER_H
