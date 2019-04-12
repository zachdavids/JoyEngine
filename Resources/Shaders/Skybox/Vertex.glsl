#version 400

layout (location = 0) in vec3 in_position;

uniform mat4 view;
uniform mat4 projection;

out VertexData
{
	vec3 uv;
} o;

void main(void)
{
	o.uv = in_position;
	gl_Position = (projection * view * vec4(in_position, 1.0)).xyww;
}