#pragma once

#include <glm/vec3.hpp>

namespace Engine
{
	struct Transform
	{
		glm::vec3 m_Position = glm::vec3(0.f);
		glm::vec3 m_Rotation = glm::vec3(0.f);
		glm::vec3 m_Scale = glm::vec3(0.f);
	};
}