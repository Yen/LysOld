#version 330 core

layout(location = 0) out vec4 out_color;

uniform sampler2D uni_textures[$TEXTURE_COUNT$];

void main(void)
{
	out_color = vec4(0.6, 0.2, 0.8, 1.0);
}