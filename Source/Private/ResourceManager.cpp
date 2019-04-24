#include "ResourceManager.h"
#include "Shader.h"
#include "Model.h"

#include <iostream>

Engine::ResourceManager* Engine::ResourceManager::m_Instance;

void Engine::ResourceManager::Create()
{
	if (m_Instance) { return; }
	m_Instance = this;

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"DefaultShader",
		"Default/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxShader",
		"Skybox/Skybox/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxConversionShader",
		"Skybox/Conversion/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxIrradianceShader",
		"Skybox/Irradiance/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxPrefilterShader",
		"Skybox/Prefilter/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"SkyboxBRDFShader",
		"Skybox/BRDF/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kShader,
		"PBRShader",
		"PBRTesselation/"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kModel,
		"Arwing",
		"Arwing/Arwing.obj"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kModel,
		"SkyboxCube",
		"Debug/Skybox.obj"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kModel,
		"Cube",
		"Debug/Cube.obj"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kModel,
		"Quad",
		"Debug/Quad.obj"
	);

	Engine::ResourceManager::Get()->AddResource(
		Engine::ResourceManager::Type::kModel,
		"Sphere",
		"Debug/Sphere.obj"
	);
}

void Engine::ResourceManager::AddResource(Type type, std::string const& name,
	std::string const& path)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.try_emplace(name, std::make_unique<Shader>(path));
		break;
	case Type::kModel:
		m_Resources.try_emplace(name, std::make_unique<Model>(path));
		break;
	}
	m_Resources.find(name)->second->Create();
}