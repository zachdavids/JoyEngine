#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include <glm/gtx/transform.hpp>
#include "stb_image.h"
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
	Game game;
	game.Start();
	return 0;
}

void Game::SetupResources()
{
	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"DefaultShader",
		"Default/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Arwing",
		"Arwing/Arwing.obj"
	);
}

void Game::Start()
{
	Engine::WindowManager window;
	window.TryCreate();	//TODO: Error handling

	SetupResources();

	//Temp---------------------------------------------
	Engine::Player player(m_ResourceManager, glm::vec3(0.f,0.f,0.f));
	Engine::Player player2(m_ResourceManager, glm::vec3(0.f, 0.f, 0.f));
	Engine::Camera camera(glm::vec3(0.f, 0.f, 3.f));
	Engine::Shader* shader = m_ResourceManager.GetResource<Engine::Shader>("DefaultShader");;
	//camera.AttachTo(&player);
	//-------------------------------------------------

	while (!window.IsCloseRequested())
	{
		window.Clear();

		//Inputs

		//Updates
		glm::vec3 light = glm::vec3(0.f);
		light.x = 2.0f * sin(glfwGetTime());
		light.y = -0.3f;
		light.z = 1.5f * cos(glfwGetTime());
		player.Update();
		player2.m_Transform.SetLocalPosition(light);
		player2.Update();
		camera.Update();

		shader->Use();
		//Renders
		shader->SetVec3("directional_light.direction", glm::vec3(light));
		shader->SetVec3("directional_light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader->SetVec3("directional_light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken the light a bit to fit the scene
		shader->SetVec3("directional_light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->SetVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		shader->SetVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));

		shader->SetFloat("material.shininess", 32.0f);
		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
		shader->SetVec3("view_position", camera.m_Transform.GetPosition());
		player.Render();
		player2.Render();


		window.SwapAndPoll();
	}

	window.Destroy();
}
