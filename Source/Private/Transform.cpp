#include "Transform.h"

void Engine::Transform::Translate(glm::vec3 const& translation, Space space)
{
	switch (space)
	{
	case Space::kLocal:
		m_LocalPosition += translation * m_LocalRotation;
		break;
	case Space::kWorld:
		m_Position += translation * m_Rotation;
		break;
	}
}

void Engine::Transform::Rotate(glm::quat const&  rotation, Space space)
{
	switch (space)
	{
	case Space::kLocal:
		m_LocalRotation *= rotation;
		m_LocalRotation = glm::normalize(m_LocalRotation);
		break;
	case Space::kWorld:
		m_Rotation *= rotation;
		m_Rotation = glm::normalize(m_Rotation);
		break;
	}
}
