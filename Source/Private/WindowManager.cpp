#include "WindowManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//TODO: Add Lua config file for Window setting

bool Engine::WindowManager::TryCreate()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(800, 600, "Wolfenstein Remastered", nullptr, nullptr);
	if (!m_Window) 
	{ 
		return false; 
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc(glfwGetProcAddress)))) 
	{
		return false; 
	}

	glViewport(0, 0, 800, 600);
	
	return true;
}

void Engine::WindowManager::Clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Engine::WindowManager::SwapAndPoll() const
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

bool Engine::WindowManager::IsCloseRequested() const
{
	return glfwWindowShouldClose(m_Window);
}

void Engine::WindowManager::Destroy()
{
	glfwTerminate();
}
