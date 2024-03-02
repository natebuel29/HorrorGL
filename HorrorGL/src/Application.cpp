#include "Application.h"

Application::Application(const char* appName, uint32_t width, uint32_t height)
{
	// glfw: initialize and configure
// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Width = width;
	m_Height = height;

	m_Window = glfwCreateWindow(m_Width, m_Height, appName, NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		throw std::runtime_error("Failed creating GLFW window");
	}

	glfwMakeContextCurrent(m_Window);

	// set callback for glfwSetFramebufferSizeCallback as a lambda
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

}

void Application::init()
{
	//OPENGL STUFF CAN GO HERE

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::runtime_error("Failed initializing GLAD");
	}
}

void Application::run()
{
	float verticies[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
	};

	//Create vertex array object
	unsigned int VAO;
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	// Create vertex buffer object for verticie data
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// bind data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);


	// --------------- CREATE SHADERS -------------------
	std::string vertSource;
	std::string fragSource;
	//read shader files and save to buffers
	try {
		std::ifstream vertStream;
		std::ifstream fragStream;
		std::stringstream vertBuffer;
		std::stringstream fragBuffer;


		vertStream.open("resources/shaders/shader.vs");
		fragStream.open("resources/shaders/shader.fs");

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
	unsigned int shaderProgram;

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);


	glDeleteShader(vertShader);
	glDeleteShader(fragShader);
	
	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	// render loop
// -----------
	while (m_Running)
	{
		// input
		// -----
		processInput();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
		m_Running = !glfwWindowShouldClose(m_Window);
	}

	this->cleanup();
}

void Application::cleanup()
{
	// glfw: terminate, clearing all previously allocated GLFW resources.
// ------------------------------------------------------------------
	glfwTerminate();
}

void Application::processInput()
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(m_Window, true);
		m_Running = false;
	}

}