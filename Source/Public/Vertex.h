#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace Engine
{
	struct Vertex
	{
		glm::vec3 m_Position;
		glm::vec2 m_UV;
		glm::vec3 m_Normal;
		glm::vec3 m_Tangent;
		glm::vec3 m_Bitangent ;
	};
}