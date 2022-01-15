#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 velocity;
layout (location = 2) in vec4 color;
layout (location = 3) in float phase;

out vec4 oColor;
out vec2 oPos;
out float oPhase;
out float oSize;


uniform vec2 uResolutionSize;
uniform vec2 uScreenSize;
uniform float uTime;
uniform mat3 uCameraMatrix;

void main()
{
    oColor = color;
    oPhase = phase;

    vec2 v = velocity * clamp(mix(1.0, 0.25, (uTime - oPhase) / 3.0), 0.0, 1.0);
    vec2 pos = position + v * (uTime - phase);
    pos = (uCameraMatrix * vec3(pos, 1.0)).xy;
    oPos = pos;
    oPos.y = uScreenSize.y - oPos.y;

    vec2 scaledPos = pos / uScreenSize;
    scaledPos.y = 1.0 - scaledPos.y;
    scaledPos = scaledPos * 2.0 - vec2(1.0);

    oSize = clamp(mix(2.0, 64.0, (uTime - oPhase) / 1.0), 2.0, 64.0) * uCameraMatrix[0][0];
    gl_PointSize = oSize / uScreenSize.y * uResolutionSize.y;
    gl_Position = vec4(scaledPos.x, scaledPos.y, 1.0, 1.0);
}