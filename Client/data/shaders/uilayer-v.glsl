#version 330 core

layout(location = 0) in vec4	in_position;
layout(location = 1) in vec2	in_uv;
layout(location = 2) in float	in_tid;
layout(location = 3) in float	in_tformat;
layout(location = 4) in vec4	in_color;

uniform mat4 uni_pr_matrix;

out data
{
	vec2 uv;
	float tid;
	float tformat;
	vec4 color;
} vert_out;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;

	vert_out.uv = in_uv;
	vert_out.tid = in_tid;
	vert_out.tformat = in_tformat;
	vert_out.color = in_color;
}