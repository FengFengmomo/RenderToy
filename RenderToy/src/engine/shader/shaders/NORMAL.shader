#SHADER VERTEX
#version 330 core
layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec3 in_Normal;

out VS_OUT {
    vec3 normal;
} vs_out;

uniform mat4 u_ViewMat;
uniform mat4 u_ModelMat;

void main()
{
    gl_Position = u_ViewMat * u_ModelMat * in_Position; 
    mat3 normalMatrix = mat3(transpose(inverse(u_ViewMat * u_ModelMat)));
    vs_out.normal = normalize(vec3(vec4(normalMatrix * in_Normal, 0.0)));
}



#SHADER GEOMETRY
#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 normal;
} gs_in[];

uniform float u_Magnitude;
  
uniform mat4 u_ProjMat;

void GenerateLine(int index)
{
    gl_Position = u_ProjMat * gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = u_ProjMat * (gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * u_Magnitude);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
}  



#SHADER FRAGMENT
#version 330 core
out vec4 fragColor;

uniform vec4 u_Color;

void main()
{
    fragColor = u_Color;
}