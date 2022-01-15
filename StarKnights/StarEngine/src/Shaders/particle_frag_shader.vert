#version 330 core

in vec4 oColor;
in vec2 oPos;
in float oPhase;
in float oSize;

out vec4 color;

uniform float uTime;
uniform vec2 uScreenSize;
uniform vec2 uResolutionSize;

void main()
{
    if ((uTime - oPhase) > 2.0)
        discard;

    float dist = distance(oPos, gl_FragCoord.xy / uResolutionSize * uScreenSize);
    if (dist > oSize / 2.0)
        discard;

    color = oColor;
    color *= clamp(mix(1.0, 0.0, (uTime - oPhase) / 2.0), 0.0, 1.0);
    color *= clamp(mix(1.0, 0.2, (uTime - oPhase) / 0.7), 0.2, 1.0);
    color.g *= clamp( mix(0.0, 1.0, (uTime - oPhase) / 0.3), 0.0, 1.0);
    color.b *= clamp(mix(0.0, 1.0, (uTime - oPhase) / 0.5), 0.0, 1.0);
    color *= clamp(mix(1.0, 0.0, dist / (oSize * 0.6)), 0.0, 1.0);
}