#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;

out vec3 f_color;

uniform float vertical_offset;

void main() {
    gl_Position = vec4(position.x + vertical_offset, position.y, 0.0F, 1.0F);

    f_color = color;
}
