#version 400

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 position;
} i;

uniform sampler2D sampler;

const vec2 inverse_atan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 vector)
{
	vec2 uv = vec2(atan(vector.z, vector.x), asin(vector.y));
	uv *= inverse_atan;
	uv += 0.5f;
	return uv;
}

void main(void)
{
	vec2 uv = SampleSphericalMap(normalize(i.position));
	vec3 color = texture(sampler, uv).rgb;
	out_color = vec4(color, 1.0f);
}