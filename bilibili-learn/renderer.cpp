//
// Created by bczhc on 8/21/21.
//

#include "renderer.h"

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const ShaderProgram &shader) const {
    va.bind();
    ib.bind();
    shader.bind();

    GL_CALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::clear() const {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
}

