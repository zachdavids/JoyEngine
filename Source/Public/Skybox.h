#pragma once

#include "ResourceManager.h"
#include "Shader.h"
#include "Model.h"

#include <string>
#include <vector>

namespace Engine
{
	class Skybox
	{
	public:
		Skybox(ResourceManager const& resource_manager);
		void Create();
		void Render();
	private:
		unsigned int m_ID;
		Shader* m_Shader;
		Model* m_Model;
	};
}

