#version 330 core

layout (location = 0) out vec4 out_color;

uniform sampler2D textures[32];

in vec4 vert_color;
in vec2 vert_coord;

void main(void)
{
	out_color = vert_color * texture(textures[0], vert_coord);
}