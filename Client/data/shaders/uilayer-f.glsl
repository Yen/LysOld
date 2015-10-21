#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D uni_textures[$SHADER_COUNT$];

in data
{
	vec2 uv;
	float tid;
	float tformat;
} frag_in;

void main(void)
{
	int tid = int(frag_in.tid);
	if (tid < 0)
	{
		out_color = vec4(0.85, 0.85, 0.85, 1.0);
	}
	else
	{
#define	ALPHA 0
#define	RGB 1
#define	RGBA 2
		switch (int(frag_in.tformat))
		{
		case ALPHA:
			out_color = vec4(1.0, 1.0, 1.0, texture(uni_textures[tid], frag_in.uv).a);
			break;
		case RGB:
			out_color = vec4(texture(uni_textures[tid], frag_in.uv).xyz, 1.0);
			break;
		case RGBA:
			out_color = texture(uni_textures[tid], frag_in.uv);
			break;
		}
	}
}