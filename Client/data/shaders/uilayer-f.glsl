#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D uni_textures[$SHADER_COUNT$];

in data
{
	vec2 uv;
	float tid;
	float tformat;
	vec4 color;
} frag_in;

vec4 getFragColor(void)
{
	return getFragColor();
}

vec4 getTextureColor(void)
{
	int tid = int(floor(frag_in.tid));

#define DEFAULT_COLOR vec4(0.85, 0.85, 0.85, 1.0)

	if (tid < 0)
	{
		return DEFAULT_COLOR;
	}
	else
	{

#define	ALPHA 0
#define	RGB 1
#define	RGBA 2

		switch (int(floor(frag_in.tformat)))
		{
		case ALPHA:
			return vec4(1.0, 1.0, 1.0, texture(uni_textures[tid], frag_in.uv).a);
		case RGB:
			return vec4(texture(uni_textures[tid], frag_in.uv).xyz, 1.0);
		case RGBA:
			return texture(uni_textures[tid], frag_in.uv);
		default:
			return DEFAULT_COLOR;
		}
	}
}

void main(void)
{
	out_color = getTextureColor() * frag_in.color;
}