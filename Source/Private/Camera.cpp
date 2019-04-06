#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Engine::Camera::Camera(glm::vec3 position)
{
	m_Transform.m_Position = position;
	CalculateViewMatrix();
}

void Engine::Camera::Update()
{
	this->GameObject::Update();
	CalculateVectors();
	CalculateViewMatrix();
	//TODO rotate camera
}

void Engine::Camera::CalculateViewMatrix()
{
	//TODO review use up vector, does it belong in transform? or camera member variable?
	m_ViewMatrix = glm::lookAt(m_Transform.m_Position, m_Transform.m_Position + m_Transform.m_Forward, glm::vec3(0.f, 1.f, 0.f));
}

void Engine::Camera::CalculateVectors()
{
	m_Transform.m_Forward.x = cos(glm::radians(m_Transform.m_Rotation.x)) * cos(glm::radians(m_Transform.m_Rotation.y));
	m_Transform.m_Forward.y = sin(glm::radians(m_Transform.m_Rotation.y));
	m_Transform.m_Forward.z = sin(glm::radians(m_Transform.m_Rotation.x)) * cos(glm::radians(m_Transform.m_Rotation.y));
	m_Transform.m_Forward = glm::normalize(m_Transform.m_Forward);
	m_Transform.m_Right = glm::normalize(glm::cross(m_Transform.m_Forward, m_Transform.m_Up));
	m_Transform.m_Up = glm::normalize(glm::cross(m_Transform.m_Right, m_Transform.m_Forward));
}
