#version 330 core

out vec4 color;

in vec2 tex_coords;
in vec3 f_color;

uniform sampler2D sampler;

void main() {
//    color = vec4(0.1F, 0.3F, 0.5F, 1.0F);
    color = texture(sampler, tex_coords) * vec4(f_color.rgb, 1.0F);
}
