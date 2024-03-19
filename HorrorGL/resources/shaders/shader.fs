#version 450 core

in vec3 vertexColor;
in vec2 TexCoord;

out vec4 FragColor;
uniform sampler2D ourTexture;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
	if(TexCoord.x < 0.0){
		FragColor = vec4(lightColor * vertexColor, 1.0);

	}
	else
	{
    FragColor = texture(ourTexture, TexCoord);
	}
}