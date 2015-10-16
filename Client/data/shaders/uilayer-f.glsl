#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D uni_textures[32];

in data
{
	vec2 uv;
	float tid;
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
		out_color = texture(uni_textures[tid], frag_in.uv);
	}
}