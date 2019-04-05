#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Player.h"

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

	//Temp
	Engine::Player m_Player(m_ResourceManager);

	while (!window.IsCloseRequested())
	{
		window.Clear();

		m_Player.Render();

		window.SwapAndPoll();
	}

	window.Destroy();
}
