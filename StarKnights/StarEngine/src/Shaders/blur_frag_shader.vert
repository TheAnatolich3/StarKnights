#version 330 core

uniform sampler2D uTexture;
uniform vec2 uDir;

in vec2 oTexCoord;
out vec4 color;

void main()
{
    color = vec4(0.0);
    vec2 off1 = vec2(1.411764705882353) * uDir;
    vec2 off2 = vec2(3.2941176470588234) * uDir;
    vec2 off3 = vec2(5.176470588235294) * uDir;
    color += texture(uTexture, oTexCoord) * 0.1964825501511404;
    color += texture(uTexture, oTexCoord + off1) * 0.2969069646728344;
    color += texture(uTexture, oTexCoord - off1) * 0.2969069646728344;
    color += texture(uTexture, oTexCoord + off2) * 0.09447039785044732;
    color += texture(uTexture, oTexCoord - off2) * 0.09447039785044732;
    color += texture(uTexture, oTexCoord + off3) * 0.010381362401148057;
    color += texture(uTexture, oTexCoord - off3) * 0.010381362401148057;
}