#version 460

uniform mat4 u_viewProjMat;
uniform mat4 u_modelMat;

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec2 a_texCoord;

out vec4 v_color;
out vec2 v_texCoord;


void main()
{
	gl_Position = u_viewProjMat * u_modelMat * vec4(a_pos, 1.0);
	v_color = vec4(a_pos, 1.0);
	v_texCoord = a_texCoord;

}