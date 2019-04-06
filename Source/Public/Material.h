#pragma once

#include "Shader.h"
#include "Texture.h"

namespace Engine
{
	class Material
	{
	public:
		Material() = default; 
	private:
		float m_Metallic{ 0.f };
		float m_Smoothness{ 0.f };
		Shader* m_Shader;
		Texture* m_Albedo;
	};
}

