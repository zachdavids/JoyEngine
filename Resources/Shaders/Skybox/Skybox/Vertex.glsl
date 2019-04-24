#version 400

layout (location = 0) in vec3 in_position;

out VertexData
{
	vec3 position;
} o;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	o.position = in_position;
	gl_Position = (projection * mat4(mat3(view)) * vec4(in_position, 1.0)).xyww;
}