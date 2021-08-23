#version 330 core

out vec4 out_color;

in vec3 f_color;

void main() {
    out_color = vec4(f_color.rgb, 1.0F);
}
