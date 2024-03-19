#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Renderer.h"
#include "Camera.h"
#include "Model.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

class Application
{
public:
	Application(const char* appName, uint32_t width, uint32_t height);
	void init();
	void run();
	void cleanup();
	void processInput();
	Camera m_Camera;

private:
	uint32_t m_Width;
	uint32_t m_Height;
	float x = 0.0f;
	float y = 0.0f;
	float z = 3.0f;
	float m_deltaTime = 0.0f;	// Time between current frame and last frame
	float m_LastFrame = 0.0f; // Time of last frame
	const float m_CameraSpeed = 2.5f; // adjust accordingly
	Renderer m_Renderer;

	glm::vec3 m_CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	GLFWwindow* m_Window;
	bool m_Running = true;

};

