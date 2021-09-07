#version 460 core

uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_tilingFactor;

in vec2 v_texCoord;
out vec4 color;

void main()
{
    color = texture(u_texture, v_texCoord * u_tilingFactor) * u_color;
}