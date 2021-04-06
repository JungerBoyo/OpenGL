#version 430 core

layout(location = 0)out vec4 Color;

uniform sampler2D uSmplr01;
in vec2 fTexCoords;

void main()
{
    Color = texture(uSmplr01, fTexCoords);
}