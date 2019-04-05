#include "Player.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>


Engine::Player::Player(ResourceManager const& resource_manager) : 
	m_Shader(resource_manager.GetResource<Shader>("DefaultShader")),
	m_Model(resource_manager.GetResource<Model>("Arwing"))
{
}

void Engine::Player::Update()
{
	GameObject::Update();
}

//TODO temporary
void Engine::Player::Render() const
{
	//TEMP
	//---------------------------------------------------------------------------
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, m_Transform.m_Position);
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(m_Transform.m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//model = glm::scale(model, m_Transform.m_Scale);

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	m_Shader->Use();
	m_Shader->SetMat4("model", model);
	m_Shader->SetMat4("view", view);
	m_Shader->SetMat4("projection", projection);
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
