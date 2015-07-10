#version 330 core

layout (location = 0) out vec4 out_color;

uniform float uni_red;

void main()
{
	out_color = vec4(uni_red, 0.0, 0.0, 1.0);
}