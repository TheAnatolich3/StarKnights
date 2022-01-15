#version 330 core

layout (location = 0) in vec2 position;

out vec2 oTexCoord;

void main()
{
    oTexCoord = position * 0.5 + vec2(0.5);
    gl_Position = vec4(position.x, position.y, 1.0, 1.0);
}