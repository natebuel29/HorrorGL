#version 450 core


in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D ourTexture;

void main()
{
	if(TexCoord.x < 0.0){
		FragColor = vec4(vertexColor, 1.0);
	}
	else
	{
    FragColor = texture(ourTexture, TexCoord);
	}
}