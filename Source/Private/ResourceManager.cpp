#include "ResourceManager.h"
#include "Shader.h"

void Engine::ResourceManager::AddResource(Type type, std::string const& name, 
	std::string const& path)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.emplace(name, std::make_unique<Shader>(path));
		break;
	}
}

void Engine::ResourceManager::CreateResources()
{
	resource_map::iterator it = m_Resources.begin();
	while (it != m_Resources.end())
	{
		it->second->Create();
	}
}
