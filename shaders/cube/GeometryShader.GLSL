#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in VS_OUT
{
    vec4 fColor;
}gs_in[];

sample out vec4 fColor;

uniform mat4 proj;
uniform vec4 camPos;

void main()
{
    vec3 a = vec3(gl_in[1].gl_Position - gl_in[0].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position - gl_in[0].gl_Position);

    vec3 normal = normalize(cross(a,b));

    if(dot(normal,vec3(gl_in[1].gl_Position) - vec3(camPos)) < 0)
    {
        vec3 v = vec3(normalize(camPos - gl_in[1].gl_Position));

        float s = clamp(100*dot((2*dot(vec3(-0.57, 0.57, 0.57), normal)*normal - vec3(-0.57, 0.57, 0.57)), v) - 97, 0.0, 1.0);
        float t = (dot(vec3(-0.57, 0.57, 0.57), normal) + 1)/2;
        
        fColor = vec4(s*vec3(1.0, 1.0, 1.0) + (1-s)*(t*(vec3(0.3, 0.2, 0.0) + vec3(0.25*gs_in[0].fColor)) + (1-t)*(vec3(-0.2, -0.2, 0.0) + vec3(0.25*gs_in[0].fColor))), 1.0);
        gl_Position = (gl_in[0].gl_Position)*proj;
        EmitVertex();

        fColor = vec4(s*vec3(1.0, 1.0, 1.0) + (1-s)*(t*(vec3(0.3, 0.2, 0.0) + vec3(0.25*gs_in[1].fColor)) + (1-t)*(vec3(-0.2, -0.2, 0.0) + vec3(0.25*gs_in[1].fColor))), 1.0);
        gl_Position = (gl_in[1].gl_Position)*proj;
        EmitVertex();

        fColor = vec4(s*vec3(1.0, 1.0, 1.0) + (1-s)*(t*(vec3(0.3, 0.2, 0.0) + vec3(0.25*gs_in[2].fColor)) + (1-t)*(vec3(-0.2, -0.2, 0.0) + vec3(0.25*gs_in[2].fColor))), 1.0);
        gl_Position = (gl_in[2].gl_Position)*proj;
        EmitVertex();

        EndPrimitive();
    }
    else
        EndPrimitive();
    
}