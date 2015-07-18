#version 330 core

layout (location = 0) out vec4 out_color;

uniform sampler2D uni_textures[32];

in vertex_data
{
	vec4 position;
	vec4 color;
	float texture;
	vec2 coords;
} frag_in;

void main(void)
{
	out_color = frag_in.color * texture(uni_textures[int(frag_in.texture)], frag_in.coords);
}