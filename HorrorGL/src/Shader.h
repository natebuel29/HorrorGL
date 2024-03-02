#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader
{
	public:
		Shader(const char* pathToVert, const char* pathToFrag);
		unsigned int getProgramID();
		void useProgram();
	private:
		unsigned int m_ShaderProgram;
};

