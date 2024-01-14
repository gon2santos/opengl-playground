#version 330 core
layout(location=0)in vec3 aPos;//primer atributo vertex pos
layout(location=1)in vec3 aColor;//segundo atributo vertex color
layout(location=2)in vec2 aTxt;//tercer atributo vertex texture pos mapping

out vec3 ourColor;
out vec2 textCoord;
void main()
{
    gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.);
    ourColor=aColor;
    textCoord=aTxt;
}

