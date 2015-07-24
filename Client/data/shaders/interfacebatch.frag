#version 330 core

layout (location = 0) out vec4 out_color;

uniform sampler2D uni_textures[32];

in data
{
	vec4 position;
	vec4 color;
	float texture;
	vec2 uv;
} frag_in;

void main(void)
{
	if(frag_in.texture + 0.5 < 0.0)
	{
		out_color = frag_in.color;
	}
	else
	{
		out_color = frag_in.color * texture(uni_textures[int(frag_in.texture + 0.5)], frag_in.uv);
	}
}
