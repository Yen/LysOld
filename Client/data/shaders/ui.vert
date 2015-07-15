#version 330 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_coord;
layout (location = 3) in float in_texture;

uniform mat4 uni_pr_matrix;

out vec4 vert_color;
out vec2 vert_coord;
out float vert_texture;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;
	vert_color = in_color;
	vert_coord = in_coord;
	vert_texture = in_texture;
}