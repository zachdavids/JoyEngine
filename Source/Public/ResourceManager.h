#pragma once

#include "Resource.h"

#include <unordered_map>
#include <memory>

namespace Engine
{
	class ResourceManager
	{
		enum class Type
		{
			kShader,
		};
	public:
		ResourceManager() = default;
		void AddResource(Type type, std::string const& name, std::string const& path_one, std::string const& path_two = "");
	private:
		using resource_map = std::unordered_map<std::string, std::unique_ptr<Resource>>;
		resource_map m_Resources;
	};
}

