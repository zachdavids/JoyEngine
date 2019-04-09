#pragma once

#include "Resource.h"
#include "Light.h"

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
		void SetFloat(std::string const& name, float value) const;
		void SetVec3(std::string const& name, glm::vec3 const& value) const;
		void SetMat4(std::string const& name, glm::mat4 const& value) const;
		void SetLight(Light const& light);
	private:
		int m_ID;
		static const std::string m_Directory;
		int LoadShader(std::string const& path, GLuint type) const;
		int Compile(GLuint vertex_id, GLuint fragment_id) const;
	};
}

