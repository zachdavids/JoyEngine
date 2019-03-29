#pragma once

#include <string>

namespace Engine
{
	class Resource
	{
	public:
		Resource() = default;
		virtual void Create() = 0;
	protected:
		std::string m_PathOne;
	};
}

