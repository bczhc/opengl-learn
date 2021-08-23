#version 330 core

out vec4 out_color;

in vec2 v_position;

void main() {
    out_color = vec4(v_position.xy, 0.0F, 1.0F);
}
