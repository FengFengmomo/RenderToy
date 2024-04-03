#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Normal;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * in_Position;
}



#SHADER FRAGMENT
#version 330 core

layout(location = 0) out vec4 fragColor;


void main()
{
    fragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}