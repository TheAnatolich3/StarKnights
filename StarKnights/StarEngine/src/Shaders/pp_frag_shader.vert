#version 330 core

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

uniform vec3 distortCoord;
uniform float uTime;

in vec2 oTexCoord;
out vec4 color;

void main()
{
    vec2 distVec = normalize(distortCoord.xy - oTexCoord);
    float distFactor = length(distortCoord.xy - oTexCoord) * distortCoord.z;

    float distCoef = mix(1.0, 0.0, distFactor * 5.0) * mix(0.0, 1.0, distFactor * 5.0) * 4.0;

    if (distFactor < 0.2)
    {
        color = texture(uTexture, oTexCoord + 1.0/distortCoord.z * distVec * sin((1.0 + cos(uTime * 4.0)) * 0.5 * distFactor * 80.0) * 0.01 * distCoef);
    }
    else
    {
        color = texture(uTexture, oTexCoord);
    }

    color += texture(uTexture2, oTexCoord) * 0.6;
}