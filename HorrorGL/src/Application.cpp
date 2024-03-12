#include "Application.h"

float lastX = 400.0f;
float lastY = 300.0f;
float pitch = 0.0f;
float yaw = -90.0f;
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);

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
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// set callback for glfwSetFramebufferSizeCallback as a lambda
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			if (firstMouse) // initially set to true
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
			lastX = xpos;
			lastY = ypos;

			const float sensitivity = 0.1f;
			xoffset *= sensitivity;
			yoffset *= sensitivity;

			yaw += xoffset;
			pitch += yoffset;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
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
		// position			// colors
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,
	};

	//Create vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create vertex buffer object for verticie data
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// bind data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	Shader shader("resources/shaders/shader.vs", "resources/shaders/shader.fs");

	// -------------------- LINK VERTEX ATTRIB POINTERS
	// params (index, size, type, normalized, stride, pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// render loop
// -----------
	while (m_Running)
	{

		float currentFrame = glfwGetTime();
		m_deltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;

		// input
		// -----
		processInput();

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useProgram();

		//apply rotation to triangle
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, glm::radians(60.0f * ((float)glfwGetTime())), glm::vec3(0.0f, 1.0f, 0.0f));

		// read this
	//	glm::vec3 cameraDirection = glm::normalize(cameraPos - glm::vec3(0.0f, 0.0f, 0.0f));
		//glm::vec3 cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
		//glm::vec3 cameraUp = glm::normalize(glm::cross(cameraDirection, cameraRight));

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		m_CameraFront = glm::normalize(direction);

		glm::mat4 view;
		view = glm::lookAt(m_CameraPos,
			m_CameraPos + m_CameraFront,
			m_CameraUp);

		/*NOTE: ran into a bug where i didn't use a view matrix and couldn't see triangle
		 this was because the "camera" and triangle were both centered at 0.
		 had to eithers translate the triangle in the -z direction
		or create a view matrix*/
		// create view (camera)
		//glm::mat4 view = glm::mat4(1.0f);
		//translate the scene in the reverse direction of where we want to move
		//view = glm::translate(view, glm::vec3(x, 0.0f, z));

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), ((float)m_Width) / ((float)m_Height), 0.1f, 100.0f);

		shader.setMat4("model", transform);
		shader.setMat4("view", view);
		shader.setMat4("projection", proj);


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
	float adjustedSpeed = m_CameraSpeed * m_deltaTime;
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_Window, true);
		m_Running = false;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_CameraPos += m_CameraFront * adjustedSpeed;

	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_CameraPos -= m_CameraFront * adjustedSpeed;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_CameraPos += glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * adjustedSpeed;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_CameraPos -= glm::normalize(glm::cross(m_CameraFront, m_CameraUp)) * adjustedSpeed;
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
}
