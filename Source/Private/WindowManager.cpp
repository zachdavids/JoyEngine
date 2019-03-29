#include "WindowManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//TODO: Add Lua config file for Window settings

int main()
{
	Engine::WindowManager window;
	if (!window.TryCreate())
	{
		return 1;
	}

	while (!window.IsCloseRequested())
	{
		window.Prepare();
	}

	window.Destroy();
	return 0;
}

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

void Engine::WindowManager::Prepare() const
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
