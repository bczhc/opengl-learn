//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_SHADER_LOCATION_H
#define OPENGL_SHADER_LOCATION_H

#include "types.h"

class ShaderLocation {
private:
    i32 location;
public:
    explicit ShaderLocation(i32 location);

    void setUniform4f(f32 v0, f32 v1, f32 v2, f32 v3) const;

    void setUniform1i(i32 i) const;
};

#endif //OPENGL_SHADER_LOCATION_H
