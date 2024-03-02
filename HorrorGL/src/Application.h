#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class Application
{
	public:
		Application(const char* appName, uint32_t width, uint32_t height);
		void init();
		void run();
		void cleanup();
		void processInput();
		
	private:
		uint32_t m_Width;
		uint32_t m_Height;
		GLFWwindow* m_Window;
		bool m_Running = true;

};

