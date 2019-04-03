#pragma once

#include "Resource.h"

namespace Engine
{
	class Texture : public Resource
	{
	public:

		enum class Type
		{
			kDiffuse,
			kSpecular,
			kNormals,
			kHeight
		};

		Texture(std::string const& path, Type type);
		void Create();
		void BindTexture() const;
	private:
		unsigned int m_ID;
		Type m_Type;
	};
}

