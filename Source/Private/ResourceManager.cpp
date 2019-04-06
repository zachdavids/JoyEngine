#include "ResourceManager.h"
#include "Shader.h"
#include "Model.h"

#include <iostream>

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