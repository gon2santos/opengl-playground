#version 330 core
layout(location=0)in vec3 aPos;//primer atributo vertex pos
layout(location=1)in vec3 aColor;//segundo atributo vertex color
layout(location=2)in vec2 aTxt;//tercer atributo vertex texture pos mapping

out vec3 ourColor;
out vec2 textCoord;

uniform mat4 transform;

void main()
{
    gl_Position=transform*vec4(aPos,1.);
    ourColor=aColor;
    textCoord=aTxt;
}

