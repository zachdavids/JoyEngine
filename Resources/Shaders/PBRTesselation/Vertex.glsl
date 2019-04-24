#version 430

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 tc_position;
out vec2 tc_uv;
out vec3 tc_normal;

void main(void)
{
	tc_position = vec3(model * vec4(in_position, 1.0f));
	tc_uv = in_uv;
	tc_normal = mat3(model) * in_normal;
}