#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"

#include <iostream>

int main()
{
	Game game;
	game.Start();
	return 0;
}

void Game::SetupResources()
{
	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"DefaultShader",
		"Resources/Shaders/Default/"
	);
}

void Game::Start()
{
	Engine::WindowManager window;
	window.TryCreate();	//TODO: Error handling

	SetupResources();

	//-----------------------------------------------------------------
	//TODO REMOVE
	std::vector<Engine::Vertex> vertices;
	vertices.push_back(Engine::Vertex{ glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f) });
	vertices.push_back(Engine::Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f) });
	vertices.push_back(Engine::Vertex{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f) });
	vertices.push_back(Engine::Vertex{ glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f) });

	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(3);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);

	Engine::Mesh test_mesh(vertices, indices);
	test_mesh.Create();

	Engine::Texture test_texture("Resources/Textures/Tiles/TileTextures.png", Engine::Texture::Type::kDiffuse);
	test_texture.Create();
	test_texture.BindTexture(0);

	Engine::Model test_model("Resources/Models/Arwing.obj");
	test_model.Create();
	//-----------------------------------------------------------------

	while (!window.IsCloseRequested())
	{
		window.Clear();

		//TEMP QUAD RENDER
		/*
		m_ResourceManager.GetResource<Engine::Shader>("DefaultShader")->Use();
		glBindVertexArray(test_mesh.GetVAO());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		*/

		//TEMP MODEL RENDER
		m_ResourceManager.GetResource<Engine::Shader>("DefaultShader")->Use();
		for (int i = 0; i != test_model.GetMeshes().size(); ++i)
		{
			for (int j = 0; j != test_model.GetTextures()[i].size(); ++j)
			{
				test_model.GetTextures()[i][j].BindTexture(j);
			}
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(test_model.GetMeshes()[i].GetVAO());
			glDrawElements(GL_TRIANGLES, test_model.GetMeshes()[i].GetSize(), GL_UNSIGNED_INT, 0);
		}

		window.SwapAndPoll();
	}

	window.Destroy();
}
