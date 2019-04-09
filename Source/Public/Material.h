#pragma once

#include <glm/vec3.hpp>

namespace Engine
{
	struct Material
	{
		float m_Shininess;
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};
}

