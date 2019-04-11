#version 400

layout(location = 0) out vec4 out_color;

struct Light
{
	vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

in VertexData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} i;

uniform vec3 light_position;
uniform vec3 view_position;
uniform Light light;
uniform Material material;
uniform sampler2D sampler;

void main(void)
{
	vec3 normal = normalize(i.normal);

	//Ambient
	float ambient_strength = 0.1f;
	vec3 ambient = light.ambient * material.ambient;

	//Diffuse
	vec3 light_direction = normalize(light.position - i.position);
	float diffuse_strength = max(dot(normal, light_direction), 0.0);
	vec3 diffuse = light.diffuse * diffuse_strength * material.diffuse;

	vec3 view_direction = normalize(view_position - i.position);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float specular_strength = 0.5 * pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	vec3 specular = light.specular * specular_strength * material.specular;

	vec3 result = ambient + diffuse + specular;
	out_color = vec4(result, 1.0f) * texture(sampler, i.uv);
}