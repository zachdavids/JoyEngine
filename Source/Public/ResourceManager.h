#pragma once

#include "Resource.h"

#include <unordered_map>
#include <memory>

namespace Engine
{
	class ResourceManager
	{
	public:
		enum class Type
		{
			kShader
		};

		ResourceManager() = default;
		void AddResource(Type type, std::string const& name, std::string const& path);
		void CreateResources();
	private:
		using resource_map = std::unordered_map<std::string, std::unique_ptr<Resource>>;
		resource_map m_Resources;
	};
}

