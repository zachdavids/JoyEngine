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
		unsigned int m_CubeMap;
		static const std::string m_Directory;
		Shader* m_Shader;
		Shader* m_ConversionShader;
		Model* m_SkyboxModel;
		void GenerateCubemap();
	};
}

