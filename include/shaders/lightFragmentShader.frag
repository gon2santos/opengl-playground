#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float lvl;

void main()
{
    FragColor=vec4(1.f,1.f,1.f,1.f);
}

