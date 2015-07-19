#version 330 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in float in_texture;
layout (location = 3) in vec2 in_coords;

uniform mat4 uni_pr_matrix;

out vertex_data
{
	vec4 position;
	vec4 color;
	float texture;
	vec2 coords;
} vert_out;

void main(void)
{
	gl_Position = uni_pr_matrix * in_position;

	vert_out.position = in_position;
	vert_out.color = in_color;
	vert_out.texture = in_texture;
	vert_out.coords = in_coords;
}