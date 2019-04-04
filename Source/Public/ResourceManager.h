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
			kShader,
			kModel
		};

		ResourceManager() = default;
		void AddResource(Type type, std::string const& name, std::string const& path);

		template <typename T>
		std::shared_ptr<T> GetResource(std::string const& name) const { return std::dynamic_pointer_cast<T>(m_Resources.find(name)->second); }

	private:
		std::unordered_map<std::string, std::shared_ptr<Resource>> m_Resources;
	};
}

