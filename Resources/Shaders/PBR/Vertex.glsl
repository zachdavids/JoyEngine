#version 410

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out VertexData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} o;

void main(void)
{
	o.position = vec3(model * vec4(in_position, 1.0f));
	o.uv = in_uv;
	o.normal = mat3(model) * in_normal;
    gl_Position =  projection * view * vec4(o.position, 1.0);
}