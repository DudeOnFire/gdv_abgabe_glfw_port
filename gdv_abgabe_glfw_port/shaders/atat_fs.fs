#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D darkMetalTexture;

void main(void)
{
	FragColor = texture(darkMetalTexture, TexCoord) * vec4(ourColor, 1.0);
}