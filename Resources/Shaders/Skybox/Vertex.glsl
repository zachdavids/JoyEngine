#version 400

layout (location = 0) in vec3 in_position;

uniform mat4 projection;
uniform mat4 view;

out VertexData
{
	vec3 position;
} o;

void main(void)
{
	o.position = in_position;
	gl_Position = (projection * view * vec4(in_position, 1.0)).xyww;
}