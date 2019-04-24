#version 400

layout(location = 0) out vec4 out_color;

in VertexData
{
	vec3 position;
} i;

uniform sampler2D cubemap;

const vec2 inv_atan = vec2(0.1591, 0.3183);

vec2 SampleSphericalMap(vec3 position)
{
    vec2 uv = vec2(atan(position.z, position.x), asin(position.y));
    uv *= inv_atan;
    uv += 0.5;
    return uv;
}

void main()
{		
    vec2 uv = SampleSphericalMap(normalize(i.position));
    vec3 color = texture(cubemap, uv).rgb;
    
    out_color = vec4(color, 1.0);
}