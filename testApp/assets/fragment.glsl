#version 330 core

uniform vec4 colorUniform = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec2 lightPos;

out vec4 color;

in vec4 colorOut;
in vec4 pos;


void main()
{
    float intensity = 1.0 / length(pos.xy - lightPos);
    color = colorOut * intensity;

}