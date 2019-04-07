#pragma once
#include "GameObject.h"

#include <glm/mat4x4.hpp>

namespace Engine
{
	class Camera : public GameObject
	{
	public:
		Camera(glm::vec3 const& position);
		void Update();
		glm::mat4 const& GetViewMatrix() const { return m_ViewMatrix; }
	private:
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);
		void CalculateViewMatrix();
	};
}

