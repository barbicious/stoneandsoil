#version 330

in vec2 v_uv;
in float v_light;

out vec4 o_color;

uniform sampler2D u_texture_sampler;

void main() {
    o_color = vec4(texture2D(u_texture_sampler, v_uv).rgb * v_light, texture2D(u_texture_sampler, v_uv).a);
}