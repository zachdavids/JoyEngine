#pragma once

#include "Resource.h"

namespace Engine
{
	class Texture : public Resource
	{
	public:
		Texture(std::string const& path, std::string const& type);
		void Create();
	private:
		unsigned int m_ID;
		std::string m_Type;
	};
}

