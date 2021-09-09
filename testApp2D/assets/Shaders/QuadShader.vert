#version 460 core


layout (std140, binding = 0) uniform PerFrameData
{
    mat4 u_viewProjMat;
};



uniform mat4 u_modelMat;

// Inputs
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texCoord;

// Outputs
layout (location = 0) out vec2 v_texCoord;

void main()
{
    gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);
    v_texCoord = a_texCoord;
}