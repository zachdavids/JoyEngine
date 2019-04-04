#pragma once

#include "Resource.h"

#include <glad/glad.h>
#include <string>

namespace Engine
{
	class Shader : public Resource
	{
	public:
		Shader(std::string const& path);
		void Create();
		void Use() const;
	private:
		int m_ID;
		static const std::string m_Directory;
		int LoadShader(std::string const& path, GLuint type) const;
		int Compile(GLuint vertex_id, GLuint fragment_id) const;
	};
}

