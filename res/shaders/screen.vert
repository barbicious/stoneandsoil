#version 330

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec2 i_uv;

out vec2 v_uv;

void main() {
    gl_Position = vec4(i_pos, 0.0, 1.0);
    v_uv = i_uv;
}