#pragma once
#include "GameObject.h"

#include <glm/mat4x4.hpp>

namespace Engine
{
	class Camera : public GameObject
	{
	public:
		Camera();
		void Update();
		glm::mat4 const& GetViewMatrix() const { return m_ViewMatrix; }
	private:
		glm::vec3 m_Target = glm::vec3(0.f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.f);

		void CalculateViewMatrix();
	};
}

