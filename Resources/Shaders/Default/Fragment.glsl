#version 400

layout(location = 0) out vec4 out_color;

struct Light
{
	float intensity;
	vec3 position;
    vec3 color;
};

in VertexData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} i;

uniform vec3 light_position;
uniform vec3 view_position;
uniform sampler2D sampler;

void main(void)
{
	vec3 normal = normalize(i.normal);

	//Ambient
	float ambient_strength = 0.1f;
	vec3 ambient = ambient_strength * vec3(1.0, 1.0, 1.0);

	//Diffuse
	vec3 light_direction = normalize(light_position - i.position);
	float diffuse_strength = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = diffuse_strength * vec3(1.0, 1.0, 1.0);

	vec3 view_direction = normalize(view_position - i.position);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float specular_strength = 0.5 * pow(max(dot(view_direction, reflection_direction), 0.0), 32);
	vec3 specular = specular_strength * vec3(1.0, 1.0, 1.0);

	vec4 result = vec4(ambient + diffuse + specular, 1.0);
	out_color = result * texture(sampler, i.uv);
}