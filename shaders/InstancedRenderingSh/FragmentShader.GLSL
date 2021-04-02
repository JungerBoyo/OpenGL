#version 430 core

layout(location = 0)out vec4 Color;
in vec4 fColor;

void main()
{
    Color = fColor;
}