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
			kHeight,
			kHDR
		};

		Texture(std::string const& path, Type type);
		void Create();
		void CreateHDR();
		void BindTexture(unsigned int index) const;
		unsigned int GetID() const { return m_ID; }
	private:
		unsigned int m_ID;
		Type m_Type;
	};
}

