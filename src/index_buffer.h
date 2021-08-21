//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_INDEX_BUFFER_H
#define OPENGL_INDEX_BUFFER_H

#include "renderer.h"

class IndexBuffer {
private:
    u32 bufferId{};
    usize count;
public:
    explicit IndexBuffer(const u32* data, usize count);

    ~IndexBuffer();

    void bind() const;

    void unbind() const;

    [[nodiscard]] usize getCount() const;
};

#endif //OPENGL_INDEX_BUFFER_H
