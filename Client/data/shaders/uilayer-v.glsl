#version 330 core

layout(location = 0) in vec4	in_position;
layout(location = 1) in vec2	in_uv;
layout(location = 2) in float	in_tid;

uniform mat4 uni_pr_matrix;

out data
{
	vec2 uv;
	float tid;
} vert_out;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;

	vert_out.uv = in_uv;
	vert_out.tid = in_tid;
}