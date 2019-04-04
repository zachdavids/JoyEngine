#include "Player.h"


Engine::Player::Player(ResourceManager const& resource_manager) : 
	m_Shader(resource_manager.GetResource<Shader>("DefaultShader")),
	m_Model(resource_manager.GetResource<Model>("Arwing"))
{
}

void Engine::Player::Create()
{
}

void Engine::Player::Update()
{
}

//TODO temporary
void Engine::Player::Render()
{
	m_Shader->Use();
	for (int i = 0; i != m_Model->GetMeshes().size(); ++i)
	{
		for (int j = 0; j != m_Model->GetTextures()[i].size(); ++j)
		{
			m_Model->GetTextures()[i][j].BindTexture(j);
		}
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_Model->GetMeshes()[i].GetVAO());
		glDrawElements(GL_TRIANGLES, m_Model->GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
	}
}
