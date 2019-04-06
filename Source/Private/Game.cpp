#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include <glm/gtx/transform.hpp>

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
	Engine::Player player(m_ResourceManager);
	Engine::Camera camera(glm::vec3(0.f, 0.f, 5.0f));
	Engine::Shader* shader = m_ResourceManager.GetResource<Engine::Shader>("DefaultShader");;
	camera.AttachTo(&player);
	//T------------------------------------------------

	while (!window.IsCloseRequested())
	{
		window.Clear();
		camera.Update();
		player.Update();
		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
		camera.GetViewMatrix();
		player.Render();

		window.SwapAndPoll();
	}

	window.Destroy();
}
