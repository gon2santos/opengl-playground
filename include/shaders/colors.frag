#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 norm=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightDir),0.);//impacto del vector luz sobre el fragmento
    vec3 diffuse=diff*lightColor;
    float specularStrength=.5;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0.),32);//reflection vector, shininess
    vec3 specular=specularStrength*spec*lightColor;
    
    float ambientStrength=.1;
    vec3 ambient=ambientStrength*lightColor;
    vec3 result=(ambient+diffuse+specular)*objectColor;
    FragColor=vec4(result,1.);
}

