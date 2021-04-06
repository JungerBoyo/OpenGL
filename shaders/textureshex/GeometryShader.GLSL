#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

uniform mat3x2 uTexCoords;

out vec2 fTexCoords;

void main()
{
    fTexCoords = uTexCoords[0];
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    fTexCoords = uTexCoords[1];
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    fTexCoords = uTexCoords[2];
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}