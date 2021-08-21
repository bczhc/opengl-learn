//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_VERTEX_BUFFER_H
#define OPENGL_VERTEX_BUFFER_H

#include "def.h"

class VertexBuffer {
private:
    u32 bufferId{};
public:
    explicit VertexBuffer(void *data, usize size);

    ~VertexBuffer();

    void bind() const;

    void unbind() const;
};

#endif //OPENGL_VERTEX_BUFFER_H
