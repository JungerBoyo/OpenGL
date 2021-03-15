#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec4 fColor;
}gs_in[];

out vec4 fColor;

uniform mat4 MVP;

void main()
{
    vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);

    vec3 normal = normalize(cross(a,b));

    if(dot(normal,vec3(gl_in[0].gl_Position)) < 0)
    {
        fColor = gs_in[0].fColor;
        gl_Position = (gl_in[0].gl_Position+vec4(0.0, 0.0, 0.0, 0.0))*MVP;
        EmitVertex();

        fColor = gs_in[1].fColor;
        gl_Position = (gl_in[1].gl_Position+vec4(0.0, 0.0, 0.0, 0.0))*MVP;
        EmitVertex();

        fColor = gs_in[2].fColor;
        gl_Position = (gl_in[2].gl_Position+vec4(0.0, 0.0, 0.0, 0.0))*MVP;
        EmitVertex();

        EndPrimitive();
    }
    else
        EndPrimitive();
    
}