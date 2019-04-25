#pragma once

#include "Map.h"
#include "Camera.h"
#include "Skybox.h"
#include "Player.h"

#include <glm/vec3.hpp>

namespace Engine
{
	class Level
	{
	public:
		Level();
		void Create();
		void Update();
		void Render();
		Skybox GetSkybox() const { return m_Skybox; }
	private:
		Player m_Player;
		Player m_Player2;
		Camera m_Camera;
		//Todo fix texture construction in skybox
		Skybox m_Skybox;
		Editor::Map m_CurrentMap;
	};
}

