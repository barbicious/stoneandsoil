#version 330

in vec2 v_uv;

out vec4 o_color;

uniform sampler2D u_texture_sampler;

void main() {
    o_color = texture2D(u_texture_sampler, v_uv);
}