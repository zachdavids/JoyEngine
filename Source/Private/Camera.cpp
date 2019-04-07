#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <GLFW/glfw3.h>

//TODO	ADD 3RD PERSON CAMERA 

Engine::Camera::Camera(glm::vec3 local_position)
{
	m_Transform.SetLocalPosition(local_position);
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

	CalculateVectors();
	CalculateViewMatrix();
}

void Engine::Camera::CalculateViewMatrix()
{
	//TODO review use up vector, does it belong in transform? or camera member variable?
	m_ViewMatrix = glm::translate(glm::mat4_cast(m_Transform.GetRotation()), -m_Transform.GetPosition());
}

void Engine::Camera::CalculateVectors()
{

}
