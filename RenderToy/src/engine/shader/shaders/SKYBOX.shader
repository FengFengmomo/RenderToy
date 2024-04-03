#SHADER VERTEX
#version 330 core

layout (location = 0) in vec3 in_Position;

out vec3 texCoord;

uniform mat4 u_ProjMat;
uniform mat4 u_ViewMat;

void main()
{
    texCoord = in_Position;
    vec4 pos = u_ProjMat * u_ViewMat * vec4(in_Position, 1.0);
    gl_Position = pos.xyww;
}  



#SHADER FRAGMENT
#version 330 core

out vec4 fragColor;

in vec3 texCoord;

uniform samplerCube skybox;

void main()
{    
    fragColor = texture(skybox, texCoord);
}