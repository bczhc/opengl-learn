//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_VERTEX_BUFFER_LAYOUT_HPP
#define OPENGL_VERTEX_BUFFER_LAYOUT_HPP

#include <vector>
#include "todo.h"
#include "cassert"
#include "def.h"
#include <GL/glew.h>

using namespace std;

struct VertexBufferElement {
    GLenum type;
    u32 count;
    bool normalized;

    static u32 getSizeOfType(GLenum type) {
        switch (type) {
            case GL_FLOAT:
                return sizeof(GLfloat);
            case GL_UNSIGNED_INT:
                return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:
                return sizeof(GLubyte);
            default:
                return 0;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    usize stride;

    template<typename>
    struct Type {
    };

public:
    explicit VertexBufferLayout() : stride(0) {}

    template<typename T>
    void push(u32 count) {
        push(count, Type<T>());
    }

    void push(u32 count, Type<f32>) {
        elements.push_back({GL_FLOAT, count, false});
        stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
    }

    void push(u32 count, Type<u32>) {
        elements.push_back({GL_UNSIGNED_INT, count, false});
        stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
    }

    void push(u32 count, Type<u8>) {
        elements.push_back({GL_UNSIGNED_BYTE, count, false});
        stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    [[nodiscard]] inline const vector<VertexBufferElement> &getElements() const {
        return elements;
    }

    [[nodiscard]] inline usize getStride() const {
        return stride;
    }
};

#endif //OPENGL_VERTEX_BUFFER_LAYOUT_HPP
