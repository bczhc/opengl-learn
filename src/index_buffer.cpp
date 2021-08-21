//
// Created by bczhc on 8/21/21.
//

#include "index_buffer.h"
#include "renderer.h"

IndexBuffer::IndexBuffer(const u32 *data, usize count) : count(count) {
    GL_CALL(glGenBuffers(1, &bufferId))
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId))
    GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(data[0]), data, GL_STATIC_DRAW))
}

IndexBuffer::~IndexBuffer() {
    GL_CALL(glDeleteBuffers(1, &bufferId))
}

void IndexBuffer::bind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId))
}

void IndexBuffer::unbind() const {
    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

usize IndexBuffer::getCount() const {
    return count;
}
