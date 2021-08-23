#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 in_tex_coords;
layout (location = 3) in vec2 in_tex2_coords;

out vec2 tex_coords;
out vec2 tex2_coords;
out vec3 f_color;

void main() {
    gl_Position = vec4(position.xy, 0.0F, 1.0F);
    tex_coords = in_tex_coords;
    tex2_coords = in_tex2_coords;
    f_color = in_color;
}
