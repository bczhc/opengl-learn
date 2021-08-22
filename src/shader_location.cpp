//
// Created by bczhc on 8/21/21.
//

#include "shader_location.h"
#include "renderer.h"

ShaderLocation::ShaderLocation(i32 location) : location(location) {}

void ShaderLocation::setUniform4f(f32 v0, f32 v1, f32 v2, f32 v3) const {
    if (location != -1) {
        GL_CALL(glUniform4f(location, v0, v1, v2, v3))
    }
}

void ShaderLocation::setUniform1i(i32 i) const {
    if (location != -1) {
        GL_CALL(glUniform1i(location, i))
    }
}
