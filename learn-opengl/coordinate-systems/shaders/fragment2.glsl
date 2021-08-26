#version 330 core

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 f_tex_coords;

void main() {
    vec4 texture1_color = texture(texture1, f_tex_coords);
    vec4 texture2_color = texture(texture2, f_tex_coords);
    if (texture2_color.a == 0.0F) {
        color = texture1_color;
    } else {
        color = mix(texture1_color, texture2_color, 0.5F);
    }
}
