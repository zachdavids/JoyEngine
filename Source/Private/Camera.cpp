#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Engine::Camera::Camera()
{

}

void Engine::Camera::Update()
{

}

void Engine::Camera::CalculateViewMatrix()
{
	//TODO review use up vector, does it belong in transform? or camera member variable?
	m_ViewMatrix = glm::lookAt(m_Transform.m_Position, m_Target, glm::vec3(0.f, 1.f, 0.f));
}
