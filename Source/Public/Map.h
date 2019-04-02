#pragma once

#include "Tile.h"

#include <vector>
#include <glm/vec2.hpp>

namespace Editor
{
	class Map
	{
	public:
		Map() = default;
		//TODO REMOVE
		void AddTile(Tile tile);
	private:
		glm::vec2 m_MapSize;
		std::vector<Tile> m_Tiles;
	};
}

