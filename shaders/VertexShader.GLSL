#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 MVP;
uniform mat4 view;
uniform mat4 model;
uniform vec4 camPos;

out VS_OUT
{
    vec4 fColor;
}vs_out;

void main()
{
    gl_Position = view*model*vPosition;
    vs_out.fColor = vColor;
    
};