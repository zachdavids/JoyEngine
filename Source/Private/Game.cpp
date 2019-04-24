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

void Game::SetupResources()
{
	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"DefaultShader",
		"Default/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxShader",
		"Skybox/Skybox/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxConversionShader",
		"Skybox/Conversion/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxIrradianceShader",
		"Skybox/Irradiance/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxPrefilterShader",
		"Skybox/Prefilter/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxBRDFShader",
		"Skybox/BRDF/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"PBRShader",
		"PBRTesselation/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Arwing",
		"Arwing/Arwing.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"SkyboxCube",
		"Debug/Skybox.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Cube",
		"Debug/Cube.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Quad",
		"Debug/Quad.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Sphere",
		"Debug/Sphere.obj"
	);
}

void Game::Start()
{
	Engine::WindowManager window;
	window.Create();

	SetupResources();

	//Temp---------------------------------------------
	Engine::Player player(m_ResourceManager, glm::vec3(0.f,0.f,0.f));
	Engine::Player player2(m_ResourceManager, glm::vec3(0.f, 0.f, 0.f));
	Engine::Camera camera(glm::vec3(0.f, 0.f, 3.f));
	Engine::Shader* shader;
	//camera.AttachTo(&player);

	Engine::Skybox skybox(m_ResourceManager);
	skybox.Create();

	//-------------------------------------------------
	shader = m_ResourceManager.GetResource<Engine::Shader>("PBRShader");
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

	shader = m_ResourceManager.GetResource<Engine::Shader>("SkyboxShader");
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

	//----------------------------------------------------------------------------------------------------------
	shader = m_ResourceManager.GetResource<Engine::Shader>("PBRShader");
	shader->Use();
	shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
	//----------------------------------------------------------------------------------------------------------

	//Reset after framebuffer
	int window_width;
	int window_height;
	glfwGetFramebufferSize(window.GetWindow(), &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);
	while (!window.IsCloseRequested())
	{
		window.Clear();

		//Inputs

		//Updates
		glm::vec3 light = glm::vec3(0.f);
		light.x = 10.0f * sin(glfwGetTime());
		light.y = 0.0f;
		light.z = 10.0f * cos(glfwGetTime());
		player.Update();
		player2.m_Transform.SetLocalPosition(light);
		player2.Update();
		camera.Update();

		shader = m_ResourceManager.GetResource<Engine::Shader>("PBRShader");
		shader->Use();
		shader->SetVec3("camera_position", camera.m_Transform.GetPosition());
		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetFloat("displacement_factor", 105.0f);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetIraddianceMap());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetPrefilterMap());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, skybox.GetBRDFMap());

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

		player.Render();
		player2.Render();

		//Lights
		for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
		{
			glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
			newPos = lightPositions[i];
			m_ResourceManager.GetResource<Engine::Shader>("PBRShader")->SetVec3("lightPositions[" + std::to_string(i) + "]", newPos);
			m_ResourceManager.GetResource<Engine::Shader>("PBRShader")->SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
		}

		//Skybox
		shader = m_ResourceManager.GetResource<Engine::Shader>("SkyboxShader");
		shader->Use();
		shader->SetMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
		shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetCubeMap());
		glBindVertexArray(m_ResourceManager.GetResource<Engine::Model>("SkyboxCube")->GetMeshes()[0].GetVAO());
		glDrawElements(GL_TRIANGLES, m_ResourceManager.GetResource<Engine::Model>("SkyboxCube")->GetMeshes()[0].GetSize(), GL_UNSIGNED_INT, 0);

		window.SwapAndPoll();
	}

	window.Destroy();
}
