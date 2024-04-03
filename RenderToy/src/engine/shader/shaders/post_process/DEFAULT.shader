#SHADER VERTEX
#version 330 core
layout (location = 0) in vec2 in_Position;
layout (location = 1) in vec2 in_TexCoord;

out vec2 texCoord;

void main()
{
    texCoord = in_TexCoord;
    gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0); 
} 



#SHADER FRAGMENT
#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, texCoord).rgb;
    fragColor = vec4(col, 1.0);
} 