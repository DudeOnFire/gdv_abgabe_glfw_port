#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VS_OUT {
	vec3 ourColor;
	vec2 TexCoord;
	vec3 FragPos;
	mat4 model;
} gs_in[];

out GS_OUT {
	vec3 ourColor;
	vec2 TexCoord;
	vec3 normal;
	vec3 FragPos;
} gs_out;

vec3 getNormalVec()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void main()
{

	gl_Position = gl_in[0].gl_Position;
	gs_out.ourColor = gs_in[0].ourColor;
	gs_out.TexCoord = gs_in[0].TexCoord;
	gs_out.FragPos = gs_in[0].FragPos;
	gs_out.normal = mat3(transpose(inverse(gs_in[0].model))) * getNormalVec();
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	gs_out.ourColor = gs_in[1].ourColor;
	gs_out.TexCoord = gs_in[1].TexCoord;
	gs_out.FragPos = gs_in[1].FragPos;
	gs_out.normal = mat3(transpose(inverse(gs_in[1].model))) * getNormalVec();
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	gs_out.ourColor = gs_in[2].ourColor;
	gs_out.TexCoord = gs_in[2].TexCoord;
	gs_out.FragPos = gs_in[2].FragPos;
	gs_out.normal = mat3(transpose(inverse(gs_in[2].model))) * getNormalVec();
	EmitVertex();

	EndPrimitive();
}

