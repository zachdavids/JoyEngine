#pragma once

#include "Mesh.h"
#include "Texture.h"
#include "Model.h"

#include <assimp/material.h>
#include <string>
#include <iostream>

struct aiNode;
struct aiScene;
struct aiMesh;
struct aiMaterial;

namespace Engine
{
	class ModelLoader
	{
	public:
		ModelLoader() = default;
		Model Load(std::string const& path) const;

	private:
		void ProcessNode(Model& model, aiNode* node, const aiScene* scene, std::string const& path) const;
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene) const;
		std::vector<Texture> ProcessTextures(aiMaterial* material, std::string const& path) const;

		std::vector<Vertex> CreateVertices(aiMesh* mesh) const;
		std::vector<unsigned int> CreateIndices(aiMesh* mesh) const;
		std::vector<Texture> CreateTextures(aiMaterial* material, aiTextureType ai_type, Texture::Type type, std::string const& path) const;
	};
}

