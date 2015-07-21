#version 330 core

layout (location = 0) out vec4 out_color;

uniform sampler2D uni_textures[32];

uniform vec3 uni_light_color;
uniform vec3 uni_light_direction;
uniform float uni_light_intensity;

in vertex_data
{
	vec4 position;
	vec4 normal;
	vec4 color;
	float texture;
	vec2 coords;
} frag_in;

void main(void)
{
	float diffuse = max(0.0, dot(normalize(frag_in.normal.xyz), -uni_light_direction));
	out_color = frag_in.color * texture(uni_textures[int(frag_in.texture + 0.5)], frag_in.coords) * vec4(uni_light_color * (uni_light_intensity + diffuse), 1.0);
}
