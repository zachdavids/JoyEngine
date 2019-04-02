#include "Mesh.h"

Engine::Mesh::Mesh(std::vector<Vertex> const& vertices, std::vector<unsigned int> const& indices) :
	m_Vertices(vertices), m_Indices(indices)
{
}

void Engine::Mesh::Create()
{
	CreateVAO();
	CreateEBO();
	CreateVBO();
	EnableAttributes();
	UnbindVAO();
}

void Engine::Mesh::CreateVAO()
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
}

void Engine::Mesh::CreateEBO()
{
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), &m_Indices[0], GL_STATIC_DRAW);
}

void Engine::Mesh::CreateVBO()
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);
}

void Engine::Mesh::EnableAttributes()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_UV));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Bitangent));
}

void Engine::Mesh::UnbindVAO()
{
	glBindVertexArray(0);
}
