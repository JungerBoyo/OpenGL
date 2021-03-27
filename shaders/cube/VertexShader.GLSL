#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform mat4 uView;
uniform mat4 uModel;

out VS_OUT
{
    vec4 fColor;
    vec3 vPosition;
}vs_out;

void main()
{
    vs_out.vPosition = (uModel*vPosition).xyz;
    gl_Position = uView * uModel * vPosition;

    vs_out.fColor = vColor;
};