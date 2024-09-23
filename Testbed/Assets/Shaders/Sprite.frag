#version 460 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D uSprite;

void main() {
    FragColor = texture(uSprite, TexCoord);
}