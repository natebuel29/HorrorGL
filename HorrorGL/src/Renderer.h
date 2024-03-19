#pragma once

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include <iostream>


//do we want a context struct?
struct OpenGLContext {
	GLuint VAO;
	GLuint lightSourceVAO;
	GLuint VBO;
	GLuint lightSourceVBO;
	GLuint dirtTextureID;
};

class Renderer
{
	public:
		Renderer() {};
		void init(int width, int height);
		void cleanup();
		void onUpdate();
		void updateViewport(int width, int height);
		Camera* getCamera();
			
	private:
		Camera m_Camera;
		Shader shader;
		Shader lightSourceShader;
		unsigned int texture;
		unsigned int VAO;
		int m_Width;
		int m_Height;
		OpenGLContext glContext;
};

