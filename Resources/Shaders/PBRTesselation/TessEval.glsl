#version 410 core

layout(triangles, equal_spacing, ccw) in;

in vec3 te_position[];
in vec2 te_uv[];
in vec3 te_normal[];

out VertexData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} o;

uniform float displacement_factor;
uniform sampler2D heightMap;

uniform mat4 projection;
uniform mat4 view;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
   	return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void)
{
   	o.uv = interpolate2D(te_uv[0], te_uv[1], te_uv[2]);
   	o.normal = normalize(interpolate3D(te_normal[0], te_normal[1], te_normal[2]));
	o.position = interpolate3D(te_position[0], te_position[1], te_position[2]);
	float displacement = texture(heightMap, o.uv).x;
	o.position += o.normal * displacement * 0.02;
   	gl_Position = projection * view * vec4(o.position, 1.0);
}