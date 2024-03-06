#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Shader
{
	public:
		Shader(const char* pathToVert, const char* pathToFrag);
		void setMat4(const char* uniform, glm::mat4& target);
		unsigned int getProgramID();
		void useProgram();
	private:
		unsigned int m_ShaderProgram;
};

