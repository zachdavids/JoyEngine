#pragma once

#include "ResourceManager.h"
#include "Level.h"

class Game
{
public:
	Game() = default;
	void Start();
private:
	void SetupResources();
	Engine::ResourceManager m_ResourceManager;
	Engine::Level m_Level;
};

