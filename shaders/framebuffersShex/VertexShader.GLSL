#version 430 core

layout(location = 0) in vec4 vPosition;

uniform mat4 uProj;
uniform mat4 uModel;
uniform mat4 uView;

void main()
{
    gl_Position = uProj * uView * (uModel*vPosition + vec4(0.0, 0.0, -7.0, 0.0));
}