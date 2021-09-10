#version 460 core


layout (std140, binding = 0) uniform PerFrameData
{
    mat4 u_viewProjMat;
};



uniform mat4 u_modelMat;

// Inputs
layout (location = 0) in vec4 a_position;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texCoord;
layout (location = 3) in float a_texID;
layout (location = 4) in float a_tilingFactor;

// Outputs
layout (location = 0) out vec2 v_texCoord;
layout (location = 1) out vec4 v_color;
layout (location = 2) out float v_texID;
layout (location = 3) out float v_tilingFactor;

void main()
{
    gl_Position = u_viewProjMat * a_position;
    v_texCoord = a_texCoord;
    v_color = a_color;
    v_texID = a_texID;
    v_tilingFactor = a_tilingFactor;
}