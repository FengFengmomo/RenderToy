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

const float offset = 1.0 / 1000.0;  

void main()
{
    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // top-left
        vec2( 0.0,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0),   // center-left
        vec2( 0.0,    0.0),   // center-center
        vec2( offset,  0.0),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    );

    float kernel[9] = float[](
        1, 1, 1,
        1, -8, 1,
        1, 1, 1  
    );
    
    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, texCoord.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }
    fragColor = vec4(col, 1.0);
}  