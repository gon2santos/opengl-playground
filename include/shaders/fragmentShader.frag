#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float lvl;

void main()
{
    FragColor=mix(texture(texture0,textCoord),texture(texture1,vec2(textCoord.x,textCoord.y)),lvl);
}

