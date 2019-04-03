#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Mesh.h"
#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "ModelLoader.h"

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
	test_texture.BindTexture();

	Engine::ModelLoader test_model;
	Engine::Model model = test_model.Load("Resources/Models/Arwing.obj");
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
		for (int i = 0; i != model.m_Meshes.size(); ++i)
		{
			model.m_Meshes[i].Create();
			for (int j = 0; j != model.m_Textures[i].size(); ++j)
			{
				model.m_Textures[i][j].Create();
				model.m_Textures[i][j].BindTexture();
			}
			glBindVertexArray(model.m_Meshes[i].GetVAO());
			glDrawElements(GL_TRIANGLES, model.m_Meshes[i].GetSize(), GL_UNSIGNED_INT, 0);
		}

		window.SwapAndPoll();
	}

	window.Destroy();
}
