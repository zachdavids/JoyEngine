#pragma once

#include "Mesh.h"
#include "Texture.h"

#include <vector>

namespace Engine
{
	struct Model
	{
		std::vector<Mesh> m_Meshes;
		std::vector<std::vector<Texture>> m_Textures;
	};
}