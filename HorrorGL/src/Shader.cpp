#include "Shader.h"

Shader::Shader(const char* pathToVert, const char* pathToFrag)
{
	// --------------- CREATE SHADERS -------------------
	std::string vertSource;
	std::string fragSource;
	//read shader files and save to buffers
	try {
		std::ifstream vertStream;
		std::ifstream fragStream;
		std::stringstream vertBuffer;
		std::stringstream fragBuffer;


		vertStream.open(pathToVert);
		fragStream.open(pathToFrag);

		vertBuffer << vertStream.rdbuf();
		fragBuffer << fragStream.rdbuf();

		vertSource = vertBuffer.str();
		fragSource = fragBuffer.str();

		vertStream.close();
		fragStream.close();
	}
	catch (const std::ifstream::failure& e) {
		std::cout << "Exception thrown when reading shader source files";
		throw e;
	}


	unsigned int vertShader;
	const char* vertCString = vertSource.c_str();

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vertCString, NULL);
	glCompileShader(vertShader);

	int success = 0;

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);

	if (!success) {

		// The maxLength includes the NULL character
		char infoLog[512];
		glGetShaderInfoLog(vertShader, 512, NULL, infoLog);


		std::cout << "Error occured when compiling vertShader: " << infoLog << std::endl;
		throw std::runtime_error("Failed to compile vertShader");
	}



	unsigned int fragShader;
	const char* fragCString = fragSource.c_str();

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragCString, NULL);
	glCompileShader(fragShader);

	success = 0;

	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);

	if (!success) {

		// The maxLength includes the NULL character
		char infoLog[512];
		glGetShaderInfoLog(fragShader, 512, NULL, infoLog);


		std::cout << "Error occured when compiling fragShader: " << infoLog << std::endl;
		throw std::runtime_error("Failed to compile fragShader");
	}



	// ---------------- CREATE SHADER PROGRAM ----------------

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertShader);
	glAttachShader(m_ShaderProgram, fragShader);
	glLinkProgram(m_ShaderProgram);
	glUseProgram(m_ShaderProgram);

	// ---------------- DELETE SHADERS ----------------
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
}

void Shader::useProgram() {
	glUseProgram(m_ShaderProgram);
}

unsigned int Shader::getProgramID() {
	return m_ShaderProgram;
}
