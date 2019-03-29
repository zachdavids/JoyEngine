#pragma once

#include "Resource.h"

#include <glad/glad.h>
#include <string>

namespace Engine
{
	class Shader : public Resource
	{
	public:
		Shader(std::string const& vertex_path, std::string const& fragment_path);
		void Create();
	private:
		int m_ID;
		std::string m_VertexPath;
		std::string m_FragmentPath;

		int LoadShader(std::string const& path, GLuint type) const;
		int Compile(GLuint vertex_id, GLuint fragment_id) const;
	};
}

