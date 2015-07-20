#version 330 core

layout (location = 0) in vec4 in_position;

uniform mat4 uni_pr_matrix;
uniform mat4 uni_vw_matrix;

void main(void)
{
	gl_Position = uni_pr_matrix * uni_vw_matrix * in_position;
}