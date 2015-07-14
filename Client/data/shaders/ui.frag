#version 330 core

layout (location = 0) out vec4 out_color;

in vec4 vert_color;

void main(void)
{
	out_color = vert_color;
}