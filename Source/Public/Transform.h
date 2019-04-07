#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Engine
{
	class Transform
	{
	public:

		enum class Space
		{
			kLocal,
			kWorld
		};

		Transform() = default;
		glm::vec3 const& GetLocalPosition() const { return m_LocalPosition; }
		glm::quat const& GetLocalRotation() const { return m_LocalRotation; }
		glm::vec3 const& GetLocalScale() const { return m_LocalScale; }
		glm::vec3 const& GetPosition() const { return m_Position; }
		glm::quat const& GetRotation() const { return m_Rotation; }
		void SetLocalPosition(glm::vec3 const& position) { m_LocalPosition = position; }
		void SetLocalRotation(glm::quat const& rotation) { m_LocalRotation = rotation; }
		void SetPosition(glm::vec3 const& position) { m_Position = position; }
		void SetRotation(glm::quat const& rotation) { m_Rotation = rotation; }
		void Translate(glm::vec3 const& translation, Space space);
		void Rotate(glm::vec3 const& rotation, Space space);
	private:
		// Represents the rotation in world space
		glm::quat m_Rotation = glm::vec3(0.f);
		// Represents the rotation in local space
		glm::quat m_LocalRotation = glm::vec3(0.f);

		// Represents the position in world space
		glm::vec3 m_Position = glm::vec3(0.f);
		// Represents the position in local space
		glm::vec3 m_LocalPosition = glm::vec3(0.f);
		// Represents the local scale
		glm::vec3 m_LocalScale = glm::vec3(1.f, 1.f, 1.f);
	};
}