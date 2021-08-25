#version 330 core

out vec4 color;

vec4 triangle_color = vec4(0.2F, 0.5F, 0.6F, 1.0F);
vec4 line_color = vec4(0.8F, triangle_color.gba);

uniform uint mark;

void main() {
    if (mark == 0U) {
        color = triangle_color;
    } else {
        color = line_color;
    }
}
