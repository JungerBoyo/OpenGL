#version 430 core

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;
layout(location = 2) in vec4 primInstancedTranslations;

out vec4 gColor;

uniform mat4 uModel[7];
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
    gl_Position = uProj * uView * (uModel[gl_InstanceID]*vPosition + primInstancedTranslations);
    gColor = vColor;
}

