#version 400

#define MAX_LIGHTS 1

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 position;
	vec2 uv;
	vec3 normal;
} i;

uniform samplerCube irradiance;
uniform samplerCube prefilter;
uniform sampler2D brdf;

uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D metallic;
uniform sampler2D roughness;
uniform sampler2D ao;
uniform sampler2D height;

uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camera_position;

const float PI = 3.14159265359;

vec3 CalculateWorldSpaceTangentNormals()
{
    vec3 tangent_normal = texture(normal, i.uv).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(i.position);
    vec3 Q2  = dFdy(i.position);
    vec2 st1 = dFdx(i.uv);
    vec2 st2 = dFdy(i.uv);

    vec3 normal   = normalize(i.normal);
    vec3 tangent  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 bitangent  = -normalize(cross(normal, tangent));
    mat3 TBN = mat3(tangent, bitangent, normal);

    return normalize(TBN * tangent_normal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 FresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}   

void main()
{		
    vec3 albedo = pow(texture(albedo, i.uv).rgb, vec3(2.2));
    float metallic = texture(metallic, i.uv).r;
    float roughness = texture(roughness, i.uv).r;
    float ao = texture(ao, i.uv).r;
       
    vec3 normal = CalculateWorldSpaceTangentNormals();
    vec3 view_direction = normalize(camera_position - i.position);
    vec3 reflect_direction = reflect(-view_direction, normal); 

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0);
    for(int x = 0; x < 4; ++x) 
    {
        vec3 light_direction = normalize(lightPositions[x] - i.position);
        vec3 half_vector = normalize(view_direction + light_direction);
        float distance = length(lightPositions[x] - i.position);
        float attenuation = 1.0 / (distance * distance);
        vec3 radiance = lightColors[x] * attenuation;

        float NDF = DistributionGGX(normal, half_vector, roughness);   
        float G   = GeometrySmith(normal, view_direction, light_direction, roughness);    
        vec3 F    = FresnelSchlick(max(dot(half_vector, view_direction), 0.0), F0);        
        
        vec3 nominator    = NDF * G * F;
        float denominator = 4 * max(dot(normal, view_direction), 0.0) * max(dot(normal, light_direction), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 specular = nominator / denominator;
        
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;	                
            
        float NdotL = max(dot(normal, light_direction), 0.0);        

        Lo += (kD * albedo / PI + specular) * radiance * NdotL;
    }   
    
    vec3 F = FresnelSchlickRoughness(max(dot(normal, view_direction), 0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = 1.0 - kS;
    kD *= 1.0 - metallic;	  
    
    vec3 irradiance = texture(irradiance, normal).rgb;
    vec3 diffuse      = irradiance * albedo;
    
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilteredColor = textureLod(prefilter, reflect_direction, roughness * MAX_REFLECTION_LOD).rgb;    
    vec2 brdf  = texture(brdf, vec2(max(dot(normal, view_direction), 0.0), roughness)).rg;
    vec3 specular = prefilteredColor * (F * brdf.x + brdf.y);

    vec3 ambient = (kD * diffuse + specular) * ao;
    
    vec3 color = ambient + Lo;
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2)); 
    out_color = vec4(color , 1.0);
}