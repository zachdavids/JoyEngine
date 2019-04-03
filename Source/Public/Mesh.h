#pragma once

#include "Vertex.h"
#include "Resource.h"

#include <glad/glad.h>
#include <vector>

namespace Engine
{
	class Mesh : public Resource
	{
	public:
		Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices);
		void Create();
		GLuint GetVAO() const { return m_VAO; }
		int GetSize() const { return m_Vertices.size(); }
	private:
		GLuint m_VAO;
		GLuint m_EBO;
		GLuint m_VBO;
		std::vector<Vertex> m_Vertices;
		std::vector<unsigned int> m_Indices;

		void CreateVAO();
		void CreateEBO();
		void CreateVBO();
		void EnableAttributes();
		void UnbindVAO();
	};
}

