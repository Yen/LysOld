#version 330 core

layout (location = 0) out vec4 out_color;

vec4 getColor();

void main()
{
	out_color = getColor();
}