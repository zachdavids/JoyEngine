#include "Game.h"
#include "WindowManager.h"

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
		"Resources/Shaders/Default/"
	);

	m_ResourceManager.CreateResources();
}

void Game::Start()
{
	Engine::WindowManager window;
	window.TryCreate();
	//TODO: Error handling

	SetupResources();

	while (!window.IsCloseRequested())
	{
		window.Prepare();
	}

	window.Destroy();
}
