#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Engine
{
	class Material
	{
	public:
		Material(); 
	private:
		float m_Metallic{ 0.f };
		float m_Smoothness{ 0.f };
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Texture> m_Albedo;
	};
}

