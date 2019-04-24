#version 400

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;

out VertexData
{
	vec2 uv;
} o;

void main()
{
	o.uv = in_uv;
	gl_Position = vec4(in_position, 1.0);
}