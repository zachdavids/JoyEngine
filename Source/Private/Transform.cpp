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

void Engine::Transform::Rotate(glm::vec3 const& rotation, Space space)
{
	switch (space)
	{
	case Space::kLocal:
		m_LocalRotation *= glm::quat(rotation);
		break;
	case Space::kWorld:
		m_Rotation *= glm::quat(rotation);
		break;
	}
}
