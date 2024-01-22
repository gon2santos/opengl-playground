#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct Material{
    sampler2D texture_diffuse1;//diffuse
    sampler2D texture_specular1;//specular
    sampler2D texture_emission1;//emission
    sampler2D texture_normal1;//normal
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    //emission
    vec3 emission=vec3(texture(material.texture_emission1,TexCoords));
    // ambient
    vec3 ambient=light.ambient*texture(material.texture_diffuse1,TexCoords).rgb;
    // diffuse
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm,lightDir),0.);
    vec3 diffuse=light.diffuse*diff*texture(material.texture_diffuse1,TexCoords).rgb;
    // specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.),32);//32==material.shininess
    vec3 specular=light.specular*spec*texture(material.texture_specular1,TexCoords).rgb;
    
    vec3 result=ambient+diffuse+specular;//+emission
    FragColor=vec4(result,1.);//arreglar specular, no esta funcando bien
}