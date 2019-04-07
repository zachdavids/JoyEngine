#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

//TODO ADD 3RD PERSON CAMERA 

Engine::Camera::Camera(glm::vec3 const& position)
{
	m_Transform.SetLocalPosition(position);
	CalculateViewMatrix();
}

void Engine::Camera::Update()
{
	if (m_Parent)
	{
		m_Transform.SetPosition(m_Parent->m_Transform.GetPosition());
		glm::vec3 parent_rotation = glm::eulerAngles(m_Parent->m_Transform.GetRotation());
		m_Transform.SetRotation(glm::quat(glm::vec3(parent_rotation.x, -parent_rotation.y, parent_rotation.z)));
	}
	else
	{
		m_Transform.SetPosition(m_Transform.GetLocalPosition());
		m_Transform.SetRotation(m_Transform.GetLocalRotation());
	}
	CalculateViewMatrix();
}

void Engine::Camera::CalculateViewMatrix()
{
	m_ViewMatrix = glm::translate(glm::mat4_cast(m_Transform.GetRotation()), -m_Transform.GetPosition());
}
