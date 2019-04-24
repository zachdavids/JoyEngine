#pragma once

#include "ResourceManager.h"
#include "WindowManager.h"
#include "Level.h"

class Game
{
public:
	Game() = default;
	void Start();
private:
	Engine::WindowManager m_WindowManager;
	Engine::ResourceManager m_ResourceManager;
	Engine::Level m_Level;
};

