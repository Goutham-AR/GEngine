#version 460

uniform sampler2D u_texture;

in vec4 v_color;
in vec2 v_texCoord;
out vec4 color;

void main()
{
	color = texture(u_texture, v_texCoord);
}