//
// Created by bczhc on 8/21/21.
//

#include "vertex_buffer.h"
#include "renderer.h"

VertexBuffer::VertexBuffer(void *data, usize size) {
    GL_CALL(glGenBuffers(1, &bufferId))
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferId))
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer() {
    GL_CALL(glDeleteBuffers(1, &bufferId))
}

void VertexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, bufferId))
}

void VertexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
}