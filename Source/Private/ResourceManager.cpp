#include "ResourceManager.h"
#include "Shader.h"

void Engine::ResourceManager::AddResource(Type type, std::string const& name, 
	std::string const& path_one, std::string const& path_two)
{
	switch (type)
	{
	case Type::kShader:
		m_Resources.emplace(name, std::make_unique<Shader>(path_one, path_two));
		break;
	}

}
