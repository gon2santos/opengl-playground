#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material{
    sampler2D texture0;//diffuse
    sampler2D texture1;//specular
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient=light.ambient*vec3(texture(material.texture0,TexCoords));
    // diffuse
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.);
    vec3 diffuse=light.diffuse*diff*vec3(texture(material.texture0,TexCoords));
    // specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.),material.shininess);
    vec3 specular=light.specular*(spec*vec3(texture(material.texture1,TexCoords)));
    
    vec3 result=ambient+diffuse+specular;
    FragColor=vec4(result,1.);
}

