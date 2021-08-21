//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_VERTEX_ARRAY_H
#define OPENGL_VERTEX_ARRAY_H

#include "vertex_buffer_layout.hpp"
#include "vertex_buffer.h"

class VertexArray {
private:
    u32 vertexArrayId;
public:
    explicit VertexArray();

    ~VertexArray();

    void bind() const;

    void unbind() const;

    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout &layout);
};

#endif //OPENGL_VERTEX_ARRAY_H
