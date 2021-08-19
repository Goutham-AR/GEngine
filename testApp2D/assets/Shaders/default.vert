#version 460 core

layout (location = 0) in vec3 a_position;


uniform mat4 u_viewProjMat;
uniform mat4 u_modelMat;


void main()
{
    gl_Position = u_viewProjMat * u_modelMat * vec4(a_position, 1.0);

}