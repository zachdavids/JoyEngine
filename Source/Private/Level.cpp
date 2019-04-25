#include "Level.h"
#include "Tile.h"

#include <GLFW/glfw3.h>

Engine::Level::Level()
{
	m_Player.m_Transform.SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	m_Player.m_Transform.SetLocalScale(glm::vec3(0.5, 0.5, 0.5));
	m_Player2.m_Transform.SetLocalPosition(glm::vec3(0.f, 0.f, 0.f));
	m_Player2.m_Transform.SetLocalScale(glm::vec3(0.5, 0.5, 0.5));
	m_Camera.m_Transform.SetLocalPosition(glm::vec3(0.f, 0.f, 3.f));
}

void Engine::Level::Create()
{
	m_Skybox.Create();
	m_Player.Create();
	m_Player2.Create();
}

void Engine::Level::Update()
{
	glm::vec3 position = glm::vec3(0.f);
	position.x = 10.0f * sin(glfwGetTime());
	position.y = 0.0f;
	position.z = 10.0f * cos(glfwGetTime());
	m_Player.Update();
	m_Player2.m_Transform.SetLocalPosition(position);
	m_Player2.Update();
	m_Camera.Update();
}

void Engine::Level::Render()
{
	m_Player.Render(m_Camera);
	m_Player2.Render(m_Camera);
	m_Skybox.Render(m_Camera);
}
