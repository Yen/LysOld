#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D uni_texture;

in data
{
	vec2 uv;
} frag_in;

void main(void)
{
	out_color = texture(uni_texture, frag_in.uv);
}