#pragma once

#include <glad/glad.h>

#include <string>

namespace Engine
{
	class Shader
	{
	public:
		Shader();
		void Create(std::string const& vertex_path, std::string const& fragment_path);
	private:
		int m_ID;

		int LoadShader(std::string const& path, GLuint type) const;
		int Compile(GLuint vertex_id, GLuint fragment_id) const;
	};
}

