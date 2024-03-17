#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 aVertexColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 vertexColor;
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
	vertexColor = aVertexColor;
	TexCoord = aTexCoord;
}