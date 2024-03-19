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
		Shader() {};
		Shader(const char* pathToVert, const char* pathToFrag);
		void setMat4(const char* uniform, glm::mat4& target);
		void setVec3(const char* uniform, glm::vec3& target);
		void setInt(const char* uniform, int target);
		unsigned int getProgramID();
		void useProgram();
	private:
		unsigned int m_ShaderProgram;
};

