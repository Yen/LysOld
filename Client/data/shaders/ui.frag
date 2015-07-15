#version 330 core

layout (location = 0) out vec4 out_color;

uniform sampler2D uni_textures[32];

in vec4 vert_color;
in vec2 vert_coord;
in float vert_texture;

void main(void)
{
	int tid = int(vert_texture);
	out_color = vert_color * texture(uni_textures[tid], vert_coord);
}