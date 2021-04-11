#version 430 core

layout(location = 0)out vec4 Color;

uniform sampler2D tex01;
uniform sampler2D tex02;

in vec2 fTexCoords;

flat in float finstance;

void main()
{

    if( int(finstance) == 0 )
        Color = texture(tex01, fTexCoords);
    else
        Color = texture(tex02, fTexCoords);
}