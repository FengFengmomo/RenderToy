#SHADER VERTEX
#version 330 core

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec3 in_Normal;
layout (location = 2) in vec2 in_TexCoord;

out vec2 texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * in_Position;
    texCoord = in_TexCoord;
};



#SHADER FRAGMENT
#version 330 core

struct Point
{
    vec3 position;  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float distance;
    float constant;
    float linear;
    float quadratic;
};

layout(location = 0) out vec4 out_Color;

in vec2 texCoord;

uniform sampler2D texture_diffuse1;
uniform bool u_DrawFlag;
uniform Point u_PointLight;

void main()
{
    // If DrawMode was set to Point or Line, set frag color to green
    if (u_DrawFlag)
    {
        vec4 texColor = texture(texture_diffuse1, texCoord);
        out_Color = texColor;
    }
    else
    {
        out_Color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
};