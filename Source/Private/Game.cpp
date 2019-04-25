#include "Game.h"
#include "WindowManager.h"

//TEMP
#include "Player.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include "Skybox.h"
#include <glm/gtx/transform.hpp>
#include "stb_image.h"
#include "GLFW/glfw3.h"

#include <iostream>

int main()
{
	Game game;
	game.Start();
	return 0;
}

void Game::Start()
{
	m_WindowManager.Create();
	m_ResourceManager.Create();
	m_Level.Create();

	Engine::Shader* shader;
	shader = Engine::ResourceManager::Get()->GetResource<Engine::Shader>("PBRShader");
	shader->Use();
	shader->SetInt("irradiance", 0);
	shader->SetInt("prefilter", 1);
	shader->SetInt("brdf", 2);
	shader->SetInt("albedo", 3);
	shader->SetInt("normal", 4);
	shader->SetInt("metallic", 5);
	shader->SetInt("roughness", 6);
	shader->SetInt("ao", 7);
	shader->SetInt("height", 8);
	shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

	shader = Engine::ResourceManager::Get()->GetResource<Engine::Shader>("SkyboxShader");
	shader->Use();
	shader->SetInt("skybox", 0);

	Engine::Texture a("Resources/Textures/PBR/alb.png", Engine::Texture::Type::kDiffuse);
	Engine::Texture n("Resources/Textures/PBR/nor.png", Engine::Texture::Type::kDiffuse);
	Engine::Texture m("Resources/Textures/PBR/met.png", Engine::Texture::Type::kDiffuse);
	Engine::Texture r("Resources/Textures/PBR/rou.png", Engine::Texture::Type::kDiffuse);
	Engine::Texture ao("Resources/Textures/PBR/ao.png", Engine::Texture::Type::kDiffuse);
	Engine::Texture h("Resources/Textures/PBR/height.png", Engine::Texture::Type::kDiffuse);
	a.Create();
	n.Create();
	m.Create();
	r.Create();
	ao.Create();
	h.Create();

	glm::vec3 lightPositions[] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3(10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3(10.0f, -10.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f),
		glm::vec3(300.0f, 300.0f, 300.0f)
	};

	//Reset after framebuffer---------------------------------------------------------------------------------------------------
	int window_width;
	int window_height;
	glfwGetFramebufferSize(Engine::WindowManager::Get()->GetWindow(), &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);
	while (!Engine::WindowManager::Get()->IsCloseRequested())
	{
		Engine::WindowManager::Get()->Clear();

		//Inputs

		//Updates
		m_Level.Update();

		shader = Engine::ResourceManager::Get()->GetResource<Engine::Shader>("PBRShader");
		shader->Use();
		//Lights
		for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		{
			glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
			newPos = lightPositions[i];
			shader->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
			shader->SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
		}
		shader->SetFloat("displacement_factor", 105.0f);

		//Remove GetSkybox()
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Level.GetSkybox().GetIraddianceMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Level.GetSkybox().GetPrefilterMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, m_Level.GetSkybox().GetBRDFMap());

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, a.GetID());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, n.GetID());
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_2D, m.GetID());
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_2D, r.GetID());
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D, ao.GetID());
		glActiveTexture(GL_TEXTURE8);
		glBindTexture(GL_TEXTURE_2D, h.GetID());

		m_Level.Render();

		Engine::WindowManager::Get()->SwapAndPoll();
	}

	Engine::WindowManager::Get()->Destroy();
}
