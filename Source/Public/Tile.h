#pragma once

#include <glm/vec2.hpp>

namespace Editor
{
	struct Tile
	{
		unsigned short m_Type;
		unsigned short m_Decor;
		unsigned short m_Actor;
		unsigned short m_Trigger;
		glm::vec2 m_Position;
	};
}

