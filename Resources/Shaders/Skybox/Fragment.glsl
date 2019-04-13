#version 400

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 position;
} i;

uniform samplerCube sampler;

void main(void)
{
	vec3 color = texture(sampler, i.position).rgb;
	color = color / (color + vec3(1.0));
	color = pow(color, vec3(1.0 / 2.2));	
	out_color = vec4(color, 1.0f);
}