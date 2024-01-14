#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 textCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    FragColor=mix(texture(texture0,textCoord),texture(texture1,textCoord)+vec4(.0627,.0196,.6588,.5),.2);
}

