#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

void main()
{

    FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
    ourColor = aColor;
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
}