#version 400

#define NPOINT_LIGHTS 4

layout(location = 0) out vec4 out_color;

struct DirectionalLight
{
	vec3 direction;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
	vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	float constant;
	float linear;
	float quadratic;
}; 

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float inner_cutoff;
	float outer_cutoff;
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

uniform vec3 view_position;
uniform DirectionalLight directional_light;
uniform Material material;
uniform sampler2D sampler;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 view_direction)
{
	float ambient_strength = 0.1f;
	vec3 light_direction = normalize(-light.direction);
	float diffuse_strength = max(dot(normal, light_direction), 0.0);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float specular_strength = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	vec3 ambient = light.ambient * material.ambient;
	vec3 diffuse = light.diffuse * diffuse_strength * material.diffuse;
	vec3 specular = light.specular * specular_strength * material.specular;
	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
	float ambient_strength = 0.1f;
	vec3 light_direction = normalize(light.position - fragment_position);
	float diffuse_strength = max(dot(normal, light_direction), 0.0);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float specular_strength = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	float distance = length(light.position - fragment_position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	vec3 ambient = light.ambient * material.ambient * attenuation;
	vec3 diffuse = light.diffuse * diffuse_strength * material.diffuse * attenuation;
	vec3 specular = light.specular * specular_strength * material.specular * attenuation;
	return ambient + diffuse + specular;
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragment_position, vec3 view_direction)
{
	float ambient_strength = 0.1f;
	vec3 light_direction = normalize(light.position - fragment_position);
	float diffuse_strength = max(dot(normal, light_direction), 0.0);
	vec3 reflection_direction = reflect(-light_direction, normal);
	float specular_strength = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
	float distance = length(light.position - fragment_position);
	float theta = dot(light_direction, normalize(-light.direction));
	float epsilon = light.inner_cutoff - light.outer_cutoff;
	float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0f, 1.0f);
	vec3 ambient = light.ambient * material.ambient * intensity;
	vec3 diffuse = light.diffuse * diffuse_strength * material.diffuse * intensity;
	vec3 specular = light.specular * specular_strength * material.specular * intensity;
	return ambient + diffuse + specular;
}

void main(void)
{
	vec3 normal = normalize(i.normal);
	vec3 view_direction = normalize(view_position - i.position);

	out_color = vec4(CalculateDirectionalLight(directional_light, normal, view_direction), 1.0f) * texture(sampler, i.uv); 
}