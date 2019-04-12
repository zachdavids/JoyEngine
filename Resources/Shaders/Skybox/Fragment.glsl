#version 400

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 uv;
} i;

uniform samplerCube sampler;

void main(void)
{
	out_color = texture(sampler, i.uv);
}