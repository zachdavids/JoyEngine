#pragma once

#include "ResourceManager.h"

class Game
{
public:
	Game() = default;
	void Start();
private:
	void SetupResources();
	Engine::ResourceManager m_ResourceManager;
};

