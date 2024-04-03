#SHADER VERTEX
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;

uniform mat4 u_MVP;
uniform mat4 u_ModelMat;

void main()
{
    fragPos = vec3(u_ModelMat * vec4(aPosition, 1.0));
    normal = mat3(transpose(inverse(u_ModelMat))) * aNormal;
    texCoord = aTexCoord;

    gl_Position = u_MVP * vec4(aPosition, 1.0);
}



#SHADER FRAGMENT
#version 330 core

#define POINT_LIGHT_COUNT 1
#define SPOT_LIGHT_COUNT 1
#define DIR_LIGHT_COUNT 1

struct PointLight
{
    vec3 position;  
    vec4 color;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;
    float angle;
    float dimAngle;
    vec4 color;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float constant;
    float linear;
    float quadratic;
};

struct DirLight
{
    vec3 direction;
    vec4 color;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct Material
{
    sampler2D tex_diffuse;
    sampler2D tex_specular;
    sampler2D tex_normal;
    float shininess;
};

layout(location = 0) out vec4 fragColor;

in vec3 fragPos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform PointLight u_PointLight[POINT_LIGHT_COUNT];
uniform SpotLight u_SpotLight[SPOT_LIGHT_COUNT];
uniform DirLight u_DirLight[DIR_LIGHT_COUNT];

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{
    vec4 result = vec4(0.0);

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(u_ViewPos - fragPos);

    // Calculate all point lights
    for (int i = 0; i < POINT_LIGHT_COUNT; i++)
    {
        result += CalcPointLight(u_PointLight[i], norm, fragPos, viewDir);
    }
    for (int i = 0; i < SPOT_LIGHT_COUNT; i++)
    {
        result += CalcSpotLight(u_SpotLight[i], norm, fragPos, viewDir);
    }
    for (int i = 0; i < DIR_LIGHT_COUNT; i++)
    {
        result += CalcDirLight(u_DirLight[i], norm, viewDir);
    }
    if (result.a < 0.1)
    {
        discard;
    }
    fragColor = result;
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec4 ambient  = light.ambient * light.color  * texture(u_Material.tex_diffuse, texCoord);
    vec4 diffuse  = light.diffuse * light.color * diff * texture(u_Material.tex_diffuse, texCoord);
    vec4 specular = light.specular * spec * texture(u_Material.tex_specular, texCoord);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec4 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
    // dim out the light
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = cos(light.angle/2) - cos(light.angle/2 + light.dimAngle);
    float intensity = clamp((theta - cos(light.angle/2 + light.dimAngle)) / epsilon, 0.0, 1.0);
    // combine results
    vec4 ambient  = light.ambient * light.color  * texture(u_Material.tex_diffuse, texCoord);
    vec4 diffuse  = light.diffuse * light.color * diff * texture(u_Material.tex_diffuse, texCoord);
    vec4 specular = light.specular * spec * texture(u_Material.tex_specular, texCoord);
    
    ambient *= attenuation;
    diffuse *= intensity * attenuation;
    specular *= intensity * attenuation;
    return (ambient + diffuse + specular);
}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // combine results
    vec4 ambient  = light.ambient * light.color * texture(u_Material.tex_diffuse, texCoord);
    vec4 diffuse  = light.diffuse * light.color * diff * texture(u_Material.tex_diffuse, texCoord);
    vec4 specular = light.specular * spec * texture(u_Material.tex_specular, texCoord);
    return (ambient + diffuse + specular);
}  