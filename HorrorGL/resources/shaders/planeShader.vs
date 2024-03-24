#version 450 

layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	FragPos = vec3(model * vec4(vertexPosition, 1.0));
    gl_Position = projection * view * vec4(FragPos, 1.0);
	Normal = mat3(transpose(inverse(model))) * vec3(0.0,1.0,0.0);  

	TexCoord = aTexCoord;
}