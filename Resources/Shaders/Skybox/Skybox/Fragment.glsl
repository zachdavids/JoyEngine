#version 400

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 position;
} i;

uniform samplerCube skybox;

void main()
{		
    vec3 color = textureLod(skybox, i.position, 0.0).rgb;
    
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2)); 
    
    out_color = vec4(color, 1.0);
}