#version 430 core

layout(location = 0) in vec4 vPosition;

layout(std140, column_major) uniform Block1
{
    mat4 uProj;
    mat4 uModel;
    mat4 uView;
    vec4 uOffset[2];
};

out float instance;

void main()
{
    gl_Position = uProj * uView * (uModel*vPosition + vec4(0.0, 0.0, -7.0, 0.0) + uOffset[gl_InstanceID]);

    instance = (gl_InstanceID == 0) ? 0.0 : 1.0;
}

