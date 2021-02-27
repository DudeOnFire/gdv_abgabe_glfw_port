#version 330 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

const float MAGNITUDE = 0.4;
vec3 normal;

uniform mat4 projection;

void generateLine(int index){
	
	gl_Position = projection * gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = projection * (gl_in[index].gl_Position + vec4(normal, 0.0) * MAGNITUDE);
	EmitVertex();
	EndPrimitive();
}

vec3 getNormalVec()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void main(){
	
	normal = getNormalVec();
	generateLine(0);
	generateLine(1);
	generateLine(2);
}