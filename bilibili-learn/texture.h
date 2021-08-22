//
// Created by bczhc on 8/22/21.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H

#include "lib/types.h"
#include <iostream>

class Texture {
private:
    u32 textureId;
    std::string filepath;
    u8 *localBuffer;
    i32 width;
    i32 height;
    i32 bpp;
public:
    explicit Texture(const char* filepath);

    ~Texture();

    void bind(u32 slot = 0);

    void unbind();
};

#endif //OPENGL_TEXTURE_H
