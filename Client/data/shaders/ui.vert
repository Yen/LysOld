#version 330 core

layout (location = 0) in vec4 in_position;

uniform mat4 uni_pr_matrix;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;
}