#version 430 core

layout (location = 0) out vec4 finalColor;

uniform vec4 uCamPos;

in GS_OUT
{
    vec4 fColor;
    vec3 vNormal;
    vec3 vPosition;
}fs_in;

uniform uint uLightCount;
uniform vec4 uLights[4];

vec3 lit(vec3 l, vec3 n, vec3 v, vec3 surfaceColor)
{
    vec3 r = reflect(-l, n);
    float s = clamp(100*dot(r, v) - 97, 0.0, 1.0);
    
    return mix(vec3(1.0, 1.0, 1.0), surfaceColor, s);
}

void main()
{
    vec3 n = fs_in.vNormal;
    vec3 v = normalize(uCamPos.xyz - fs_in.vPosition);
    
    finalColor = 0.3*fs_in.fColor;

    for(int i=0; i<uLightCount; i+=2)
    {
        vec3 l = normalize(uLights[i].xyz - uCamPos.xyz);
        float towardLightperc = clamp(dot(l, n), 0.0, 1.0);
        finalColor.rgb += towardLightperc * uLights[i+1].rgb * lit(l, n, v, fs_in.fColor.rgb);
    }
};