#version 400

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

//TODO: Switch to uniform block
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

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
	o.normal = mat3(transpose(inverse(model))) * in_normal;  
	gl_Position = projection * view * model * vec4(in_position, 1.0);
}