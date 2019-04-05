#pragma once

#include "Mesh.h"
#include "Texture.h"

#include <assimp/material.h>
#include <string>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Engine
{
	class Model : public Resource
	{
	public:
		Model(std::string const& path);
		void Create();
		std::vector<Mesh>& GetMeshes() { return m_Meshes; }
		std::vector<std::vector<Texture>>& GetTextures() { return m_Textures; }

	private:
		std::vector<Mesh> m_Meshes;
		std::vector<std::vector<Texture>> m_Textures;
		static const std::string m_Directory;

		void ProcessNode(aiNode* node, const aiScene* scene);
		void ProcessMesh(aiMesh* mesh, const aiScene* scene);
		void ProcessTextures(aiMaterial* material);

		std::vector<Vertex> CreateVertices(aiMesh* mesh) const;
		std::vector<unsigned int> CreateIndices(aiMesh* mesh) const;
		std::vector<Texture> CreateTextures(aiMaterial* material, aiTextureType ai_type, Texture::Type type) const;
	};
}

