#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 projMat = mat4(1.0);
uniform mat4 viewMat = mat4(1.0);
uniform mat4 modelMat = mat4(1.0);

out vec4 pos;
out vec4 colorOut;

void main()
{
    gl_Position =  projMat * viewMat * modelMat * position;
    pos = modelMat * position;
    colorOut = color;
}