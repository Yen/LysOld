#version 330 core

layout (location = 0) in vec4 in_position;
layout (location = 4) in vec2 in_uv;

out data
{
	vec2 uv;
} vert_out;

void main(void)
{
	vert_out.uv = in_uv;
	gl_Position = in_position;
}