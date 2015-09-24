#version 330 core

layout(location = 0) in vec4 in_position;
layout(location = 1) in vec2 in_uv;

out data
{
	vec2 uv;
} vert_out;

void main(void)
{
	gl_Position = in_position;

	vert_out.uv = in_uv;
}