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
		"Skybox/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kShader,
		"PBRShader",
		"PBR/"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Arwing",
		"Arwing/Arwing.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Skybox",
		"Debug/Skybox.obj"
	);

	m_ResourceManager.AddResource(
		Engine::ResourceManager::Type::kModel,
		"Cube",
		"Debug/Cube.obj"
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
	window.TryCreate();	//TODO: Error handling

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

		//Renders
		//GameObjects
		//shader = m_ResourceManager.GetResource<Engine::Shader>("DefaultShader");
		//shader->Use();
		//shader->SetVec3("directional_light.direction", glm::vec3(light));
		//shader->SetVec3("directional_light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		//shader->SetVec3("directional_light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken the light a bit to fit the scene
		//shader->SetVec3("directional_light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		shader = m_ResourceManager.GetResource<Engine::Shader>("PBRShader");
		shader->Use();
		shader->SetVec3("light_position", glm::vec3(-10, 10, 10));
		shader->SetVec3("light_color", glm::vec3(300.0f, 300.0f, 300.0f));
		shader->SetVec3("camera_position", camera.m_Transform.GetPosition());

		shader->SetVec3("material.albedo", glm::vec3(0.5f, 0.0f, 0.0f));
		shader->SetFloat("material.metallic", 0.0f);
		shader->SetFloat("material.roughness", 0.1f);
		shader->SetFloat("material.ao", 1.0f);

		shader->SetMat4("view", camera.GetViewMatrix());
		shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));

		player.Render();
		player2.Render();

		//Skybox
		shader = m_ResourceManager.GetResource<Engine::Shader>("SkyboxShader");
		shader->Use();
		shader->SetMat4("view", glm::mat4(glm::mat3(camera.GetViewMatrix())));
		shader->SetMat4("projection", glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f));
		skybox.Render();

		window.SwapAndPoll();
	}

	window.Destroy();
}
