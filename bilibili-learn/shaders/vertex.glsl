#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

void main() {
    gl_Position = vec4(position.x, position.y, 0.0F, 1.0F);
    v_TexCoord = texCoord;
}
