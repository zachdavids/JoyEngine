#pragma once

#include <glm/vec3.hpp>

namespace Engine
{
	struct Transform
	{
		// World position
		glm::vec3 m_Position = glm::vec3(0.f);
		// World rotation (pitch, yaw, roll)
		glm::vec3 m_Rotation = glm::vec3(0.f);

		// Local position
		glm::vec3 m_LocalPosition = glm::vec3(0.f);
		// Local rotation (pitch, yaw, roll)
		glm::vec3 m_LocalRotation = glm::vec3(0.f);
		// Local rotation
		glm::vec3 m_LocalScale = glm::vec3(1.f, 1.f, 1.f);

		//Orientation
		//Todo Quaternion
		glm::vec3 m_Forward = glm::vec3(0.f, 0.f, -1.f);
		glm::vec3 m_Up = glm::vec3(0.f, 1.f, 0.f);
		glm::vec3 m_Right = glm::vec3(-1.f, 0.f, 0.f);
	};
}