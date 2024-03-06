#version 450 core

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 aVertexColor;

uniform mat4 transform;
out vec3 vertexColor;

void main()
{
	gl_Position = transform * vec4(vertexPosition, 1.0);
	vertexColor = aVertexColor;
}