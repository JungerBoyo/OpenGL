#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat3x2 uTexCoords;

out vec2 fTexCoords;

in float instance[];
flat out float finstance;

void main()
{
    fTexCoords = uTexCoords[0];
    finstance = instance[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    fTexCoords = uTexCoords[1];
    finstance = instance[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    fTexCoords = uTexCoords[2];
    finstance = instance[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}