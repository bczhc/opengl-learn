//
// Created by bczhc on 8/22/21.
//

#include "texture.h"
#include "renderer.h"
#include "lib/stb_image.h"

Texture::Texture(const char *filepath) : filepath(filepath), textureId(0), width(0), height(0), bpp(0), localBuffer(
        nullptr) {
    stbi_set_flip_vertically_on_load(1);
    localBuffer = stbi_load(this->filepath.c_str(), &width, &height, &bpp, STBI_rgb_alpha);

    GL_CALL(glGenTextures(1, &textureId))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureId))

    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE))
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE))

    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));

    // this is just `free()`, and `free()` is null-pointer-safe
    stbi_image_free(localBuffer);
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &textureId))
}

void Texture::bind(u32 slot) {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot))
    GL_CALL(glBindTexture(GL_TEXTURE_2D, textureId))
}

void Texture::unbind() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
}
