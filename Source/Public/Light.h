#pragma once

#include "GameObject.h"

namespace Engine
{
	struct Light
	{
		glm::vec3 m_Position = glm::vec3(0.f, 0.f, 0.f);
		float m_Intensity;
		glm::vec3 m_Direction = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 0.98f);
	};
}