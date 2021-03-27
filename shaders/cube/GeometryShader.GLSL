#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec4 fColor;
    vec3 vPosition;
}gs_in[];

out GS_OUT
{
    vec4 fColor;
    vec3 vNormal;
    vec3 vPosition;
}gs_out;

uniform mat4 uProj;
uniform vec4 uCamPos;

void main()
{
    vec3 normal = normalize(cross( (gl_in[1].gl_Position - gl_in[0].gl_Position).xyz, (gl_in[2].gl_Position - gl_in[0].gl_Position).xyz));
    vec3 worldNormal = normalize(cross( (gs_in[1].vPosition - gs_in[0].vPosition).xyz, (gs_in[2].vPosition - gs_in[0].vPosition).xyz));

    if(dot(normal, (gl_in[1].gl_Position.xyz) - (uCamPos.xyz)) < 0)
    {
        gs_out.fColor = gs_in[0].fColor;
        gs_out.vNormal = worldNormal;
        gs_out.vPosition = gs_in[0].vPosition;
        gl_Position = (gl_in[0].gl_Position)*uProj; // 1
        EmitVertex();

        gs_out.fColor = gs_in[1].fColor;
        gs_out.vNormal = worldNormal;
        gs_out.vPosition = gs_in[1].vPosition;
        gl_Position = (gl_in[1].gl_Position)*uProj; // 2
        EmitVertex();

        gs_out.fColor = gs_in[2].fColor;
        gs_out.vNormal = worldNormal;
         gs_out.vPosition = gs_in[2].vPosition;
        gl_Position = (gl_in[2].gl_Position)*uProj; // 3
        EmitVertex();

        EndPrimitive();
    }
    else
        EndPrimitive();
}