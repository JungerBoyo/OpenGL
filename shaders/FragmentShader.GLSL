#version 430 core

layout (location = 0) out vec4 finalColor;

in vec4 fColor;

void main()
{
    finalColor = fColor;
};