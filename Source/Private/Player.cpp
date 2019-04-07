#include "Player.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>


Engine::Player::Player(ResourceManager const& resource_manager, glm::vec3 position) :
	m_Shader(resource_manager.GetResource<Shader>("DefaultShader")),
	m_Model(resource_manager.GetResource<Model>("Arwing"))
{
	m_Transform.SetLocalPosition(position);
}

void Engine::Player::Update()
{
	m_Transform.SetLocalPosition(glm::vec3(0.f, 0.f, (float)glfwGetTime() * -1.5));
	m_Transform.SetLocalRotation(glm::quat(glm::vec3(0.f, (float)glfwGetTime() * glm::radians(25.0f), 0.f)));

	GameObject::Update();
}

//TODO temporary
void Engine::Player::Render() const
{
	//TEMP
	//---------------------------------------------------------------------------
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_Transform.GetPosition());
	model *= glm::mat4_cast(m_Transform.GetRotation());
	model = glm::scale(model, m_Transform.GetLocalScale());

	m_Shader->Use();
	m_Shader->SetMat4("model", model);
	//---------------------------------------------------------------------------

	for (int i = 0; i != m_Model->GetMeshes().size(); ++i)
	{
		for (int j = 0; j != m_Model->GetTextures()[i].size(); ++j)
		{
			m_Model->GetTextures()[i][j].BindTexture(j);
		}
		glBindVertexArray(m_Model->GetMeshes()[i].GetVAO());
		glDrawElements(GL_TRIANGLES, m_Model->GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
	}
}
