#include "Player.h"

#include "ResourceManager.h"

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtx/transform.hpp>

Engine::Player::Player(glm::vec3 position) :
	m_Shader(ResourceManager::Get()->GetResource<Shader>("PBRShader")),
	m_Model(ResourceManager::Get()->GetResource<Model>("Sphere"))
{
	m_Transform.SetLocalPosition(position);
	m_Transform.SetLocalScale(glm::vec3(0.5, 0.5, 0.5));
}

void Engine::Player::Update()
{
	//m_Transform.SetLocalPosition(glm::vec3(0.f, 0.f, (float)glfwGetTime() * -1.5));
	m_Transform.SetLocalRotation(glm::angleAxis(glm::radians((float)glfwGetTime() * 12), glm::vec3(0.f, 1.f, 0.f)));

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
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawElements(GL_PATCHES, m_Model->GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
	}
}
