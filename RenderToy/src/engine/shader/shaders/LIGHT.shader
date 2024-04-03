#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 in_Position;

uniform mat4 u_MVP;
uniform vec3 u_ViewPos;

void main()
{
    float distance = length(u_ViewPos - vec3(in_Position)) / 20;
    mat4 scale = mat4(
        distance, 0.0, 0.0, 0.0,
        0.0, distance, 0.0, 0.0,
        0.0, 0.0, distance, 0.0,
        0.0, 0.0, 0.0, 1.0
    );
    gl_Position = u_MVP * scale * in_Position;
}



#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 fragColor;

uniform vec4 u_Color;

void main()
{
    fragColor = u_Color;
}