#version 330 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec4 in_color;

uniform mat4 uni_pr_matrix;

out vec4 vert_color;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;
	vert_color = in_color;
}