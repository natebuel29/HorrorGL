#include "Application.h"

float lastX = 400.0f;
float lastY = 300.0f;
float pitch = 0.0f;
float yaw = -90.0f;
bool firstMouse = true;

//https://stackoverflow.com/questions/36659599/glfw-keycallback-userpointer-not-carrying-data

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

	m_Renderer = Renderer();

	glfwSetWindowUserPointer(m_Window, &m_Renderer);

	glfwMakeContextCurrent(m_Window);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// set callback for glfwSetFramebufferSizeCallback as a lambda
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			Renderer* renderer = (Renderer*)glfwGetWindowUserPointer(window);
			renderer->updateViewport(width, height);
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			Renderer* renderer = (Renderer*)glfwGetWindowUserPointer(window);

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

			renderer->getCamera()->updateCameraRotation(xoffset, yoffset);
		});

}

void Application::init()
{
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::runtime_error("Failed initializing GLAD");
	}

	m_Renderer.init(m_Width, m_Height);
}

void Application::run()
{
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

		m_Renderer.onUpdate();

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
	m_Renderer.cleanup();
	glfwTerminate();
}

void Application::processInput()
{
	glm::vec3 direction(0.0f, 0.0f, 0.0f);
	float adjustedSpeed = m_CameraSpeed * m_deltaTime;
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_Window, true);
		m_Running = false;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Renderer.getCamera()->moveCamera(FORWARD, m_deltaTime);
	}
	if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Renderer.getCamera()->moveCamera(BACKWARD, m_deltaTime);

	}
	if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Renderer.getCamera()->moveCamera(RIGHT, m_deltaTime);

	}
	if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Renderer.getCamera()->moveCamera(LEFT, m_deltaTime);
	}


}
