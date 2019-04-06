#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

//TODO	ADD 3RD PERSON CAMERA 
//		RESTRICT DISTANCE BETWEEN PARENT AND CHILD IN FPS CAMERA

Engine::Camera::Camera(glm::vec3 local_position)
{
	m_Transform.m_LocalPosition = local_position;
	m_Transform.m_LocalRotation = glm::vec3(0.f, -90.f, 0.f);
	CalculateViewMatrix();
}

void Engine::Camera::Update()
{
	if (m_Parent)
	{
		m_Transform.m_Position = m_Parent->m_Transform.m_Position;

		m_Transform.m_Rotation.x = m_Parent->m_Transform.m_Rotation.x + m_Transform.m_LocalRotation.x;
		m_Transform.m_Rotation.y = -m_Parent->m_Transform.m_Rotation.y + m_Transform.m_LocalRotation.y;
		m_Transform.m_Rotation.z = m_Parent->m_Transform.m_Rotation.z; +m_Transform.m_LocalRotation.z;
	}
	else
	{
		m_Transform.m_Position = m_Transform.m_LocalPosition;
		m_Transform.m_Rotation = m_Transform.m_LocalRotation;
	}

	CalculateVectors();
	CalculateViewMatrix();
}

void Engine::Camera::CalculateViewMatrix()
{
	//TODO review use up vector, does it belong in transform? or camera member variable?
	m_ViewMatrix = glm::lookAt(m_Transform.m_Position, m_Transform.m_Position + m_Transform.m_Forward, glm::vec3(0.f, 1.f, 0.f));
}

void Engine::Camera::CalculateVectors()
{
	m_Transform.m_Forward.x = cos(glm::radians(m_Transform.m_Rotation.y)) * cos(glm::radians(m_Transform.m_Rotation.x));
	m_Transform.m_Forward.y = sin(glm::radians(m_Transform.m_Rotation.x));
	m_Transform.m_Forward.z = sin(glm::radians(m_Transform.m_Rotation.y)) * cos(glm::radians(m_Transform.m_Rotation.x));
	m_Transform.m_Forward = glm::normalize(m_Transform.m_Forward);
	m_Transform.m_Right = glm::normalize(glm::cross(m_Transform.m_Forward, m_Transform.m_Up));
	m_Transform.m_Up = glm::normalize(glm::cross(m_Transform.m_Right, m_Transform.m_Forward));
}
