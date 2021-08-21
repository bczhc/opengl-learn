//
// Created by bczhc on 8/21/21.
//

#include "renderer.h"

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void glLogError(GLenum error, const char *file, u32 line, const char *lineCode) {
    cout << "[OpenGL Error] (" << error << ") " << file << ' ' << line << ' ' << lineCode << endl;
}

bool glCheckError(const char *file, u32 line, const char *lineCode) {
    GLenum error;
    if ((error = glGetError()) != GL_NO_ERROR) {
        glLogError(error, file, line, lineCode);
        return true;
    }
    return false;
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    va.bind();
    ib.bind();
    shader.bind();

    GL_CALL(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr))
}

void Renderer::clear() const {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT))
}

