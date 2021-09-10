#version 460 core

// Uniforms
uniform sampler2D u_textures[32];


// Inputs
layout (location = 0) in vec2 v_texCoord;
layout (location = 1) in vec4 v_color;
layout (location = 2) in float v_texID;
layout (location = 3) in float v_tilingFactor;

// Outputs
layout (location = 0) out vec4 color;


void main()
{
    color = texture(u_textures[int(v_texID)], v_texCoord * v_tilingFactor) * v_color;
}