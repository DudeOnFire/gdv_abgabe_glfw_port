#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 view;
uniform mat4 model;
uniform mat4 projection;


out VS_OUT {
	vec3 ourColor;
	vec2 TexCoord;
	vec3 FragPos;
	mat4 model;
} vs_out;

void main()
{
	gl_Position = projection * view  * model * vec4(aPos, 1.0);
	vs_out.ourColor = aColor;
	vs_out.TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
	vs_out.model = model;
}