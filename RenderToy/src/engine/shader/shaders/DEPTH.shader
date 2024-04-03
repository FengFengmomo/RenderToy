#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 in_Position;

out vec3 fragPos;

uniform mat4 u_MVP;
uniform mat4 u_ModelMat;

void main()
{
    fragPos = vec3(u_ModelMat * in_Position);
    gl_Position = u_MVP * in_Position;
}



#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 fragColor;

in vec3 fragPos;

uniform float u_NearPlane;
uniform float u_FarPlane;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * u_NearPlane * u_FarPlane) / (u_FarPlane + u_NearPlane - z * (u_FarPlane - u_NearPlane));	
}

void main()
{
    // divide by far for demonstration
    float depth = LinearizeDepth(gl_FragCoord.z) / u_FarPlane; 
    fragColor = vec4(vec3(depth), 1.0);
}