#include "Player.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>


Engine::Player::Player(ResourceManager const& resource_manager, glm::vec3 position) :
	m_Shader(resource_manager.GetResource<Shader>("DefaultShader")),
	m_Model(resource_manager.GetResource<Model>("Arwing"))
{
	m_Transform.m_LocalPosition = position;
}

void Engine::Player::Update()
{
	GameObject::Update();
	//m_Transform.m_Position += glm::vec3(0.f, 0.f, 0.01);
	m_Transform.m_LocalRotation.y = (float)glfwGetTime() * glm::radians(50.0f) * 15;
}

//TODO temporary
void Engine::Player::Render() const
{
	//TEMP
	//---------------------------------------------------------------------------
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_Transform.m_Position);
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, m_Transform.m_LocalScale);

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
