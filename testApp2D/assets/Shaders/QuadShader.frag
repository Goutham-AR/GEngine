#version 460 core

// Uniforms
uniform sampler2D u_texture;
uniform vec4 u_color;
uniform float u_tilingFactor;



// Inputs
layout (location = 0) in vec2 v_texCoord;

// Outputs
layout (location = 0) out vec4 color;

void main()
{
    color = texture(u_texture, v_texCoord * u_tilingFactor) * u_color;
}