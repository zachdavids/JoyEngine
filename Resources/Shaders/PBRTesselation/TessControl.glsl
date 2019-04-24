#version 430

layout (vertices = 3) out;

in vec3 tc_position[];
in vec2 tc_uv[];
in vec3 tc_normal[];

out vec3 te_position[];
out	vec2 te_uv[];
out	vec3 te_normal[];

uniform vec3 camera_position;

float GetTessLevel(float p1, float p2)
{
    float avg_distance = (p1 + p2) / 2.0;

    if (avg_distance <= 2.0) 
	{
        return 10.0;
    }
    else if (avg_distance <= 5.0) 
	{
        return 7.0;
    }
    else 
	{
        return 3.0;
    }
}

void main(void)
{
    te_position[gl_InvocationID] = tc_position[gl_InvocationID];
    te_normal[gl_InvocationID]   = tc_normal[gl_InvocationID];
    te_uv[gl_InvocationID] = tc_uv[gl_InvocationID];
	    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(camera_position, te_position[0]);
    float EyeToVertexDistance1 = distance(camera_position, te_position[1]);
    float EyeToVertexDistance2 = distance(camera_position, te_position[2]);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = GetTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[1] = GetTessLevel(EyeToVertexDistance2, EyeToVertexDistance0);
    gl_TessLevelOuter[2] = GetTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}