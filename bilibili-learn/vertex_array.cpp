//
// Created by bczhc on 8/21/21.
//

#include "vertex_array.h"
#include "opengl-lib/error_check.h"

VertexArray::VertexArray() {
    GL_CALL(glGenVertexArrays(1, &vertexArrayId))
}

VertexArray::~VertexArray() {
    GL_CALL(glDeleteVertexArrays(1, &vertexArrayId))
}

void VertexArray::bind() const {
    GL_CALL(glBindVertexArray(vertexArrayId))
}

void VertexArray::unbind() const {
    GL_CALL(glBindVertexArray(0))
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const vector<VertexBufferElement> &elements = layout.getElements();
    usize offset = 0;
    for (usize i = 0; i < elements.size(); ++i) {
        const auto element = elements[i];
        GL_CALL(glEnableVertexAttribArray(i))
        GL_CALL(glVertexAttribPointer(i, (GLint) element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE,
                                      (GLsizei) layout.getStride(), (const void *) offset))
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
