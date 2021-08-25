//
// Created by bczhc on 8/21/21.
//

#ifndef OPENGL_SHADER_LOCATION_H
#define OPENGL_SHADER_LOCATION_H

#include "lib/types.h"

class ShaderLocation {
private:
    i32 location;
public:
    explicit ShaderLocation(i32 location);

    void setUniform(f32 v0, f32 v1, f32 v2, f32 v3) const;

    void setUniform(i32 i) const;

    void setUniform(f32 f) const;

    void setUniform(bool b) const;
};

#endif //OPENGL_SHADER_LOCATION_H
