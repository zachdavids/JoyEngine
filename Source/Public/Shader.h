#pragma once

#include "Resource.h"

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>

namespace Engine
{
	class Shader : public Resource
	{
	public:
		Shader(std::string const& path);
		void Create();
		void Use() const;
		void SetMat4(std::string const& name, glm::mat4 value) const;
	private:
		int m_ID;
		static const std::string m_Directory;
		int LoadShader(std::string const& path, GLuint type) const;
		int Compile(GLuint vertex_id, GLuint fragment_id) const;
	};
}

