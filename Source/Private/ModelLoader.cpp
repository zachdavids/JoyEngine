#include "ModelLoader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

///MODELS LOADED MUST HAVE CREATE() CALLED ON MESHES AND TEXTURES
///TODO: TIE INTO RESOURCEMANAGER

Engine::Model Engine::ModelLoader::Load(std::string const& path) const
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

	Model model;
	ProcessNode(model, scene->mRootNode, scene, path);
	return model;
}

void Engine::ModelLoader::ProcessNode(Model& out_model, aiNode* node, const aiScene* scene, std::string const& path) const
{
	for (unsigned int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		out_model.m_Meshes.push_back(ProcessMesh(mesh, scene));
		out_model.m_Textures.push_back(ProcessTextures(scene->mMaterials[mesh->mMaterialIndex], path));
	}
	for (unsigned int i = 0; i != node->mNumChildren; ++i)
	{
		ProcessNode(out_model, node->mChildren[i], scene, path);
	}
}

Engine::Mesh Engine::ModelLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene) const
{
	std::vector<Vertex> vertices = CreateVertices(mesh);
	std::vector<unsigned int> indices = CreateIndices(mesh);

	return Mesh(vertices, indices);
}

std::vector<Engine::Vertex> Engine::ModelLoader::CreateVertices(aiMesh* mesh) const
{
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.m_Position.x = mesh->mVertices[i].x;
		vertex.m_Position.y = mesh->mVertices[i].y;
		vertex.m_Position.z = mesh->mVertices[i].z;

		if (mesh->mNormals)
		{
			vertex.m_Normal.x = mesh->mNormals[i].x;
			vertex.m_Normal.y = mesh->mNormals[i].y;
			vertex.m_Normal.z = mesh->mNormals[i].z;
		}

		if (mesh->mTextureCoords[0])
		{
			vertex.m_UV.x = mesh->mTextureCoords[0][i].x;
			vertex.m_UV.y = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vertex.m_Tangent.x = mesh->mTangents[i].x;
			vertex.m_Tangent.y = mesh->mTangents[i].y;
			vertex.m_Tangent.z = mesh->mTangents[i].z;

			vertex.m_Bitangent.x = mesh->mBitangents[i].x;
			vertex.m_Bitangent.y = mesh->mBitangents[i].y;
			vertex.m_Bitangent.z = mesh->mBitangents[i].z;
		}
		vertices.push_back(vertex);
	}
	return vertices;
}

std::vector<unsigned int> Engine::ModelLoader::CreateIndices(aiMesh* mesh) const
{
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i != mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j != face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	return indices;
}

std::vector<Engine::Texture> Engine::ModelLoader::ProcessTextures(aiMaterial* material, std::string const& path) const
{
	std::vector<Texture> textures;
	std::vector<Texture> diffuse = CreateTextures(material, aiTextureType_DIFFUSE, Texture::Type::kDiffuse, path);
	textures.insert(std::end(textures), std::begin(diffuse), std::end(diffuse));

	std::vector<Texture> specular = CreateTextures(material, aiTextureType_SPECULAR, Texture::Type::kSpecular, path);
	textures.insert(std::end(textures), std::begin(specular), std::end(specular));

	std::vector<Texture> normal = CreateTextures(material, aiTextureType_NORMALS, Texture::Type::kNormals, path);
	textures.insert(std::end(textures), std::begin(normal), std::end(normal));

	std::vector<Texture> height = CreateTextures(material, aiTextureType_HEIGHT, Texture::Type::kHeight, path);
	textures.insert(std::end(textures), std::begin(height), std::end(height));
	return textures;
}

std::vector<Engine::Texture> Engine::ModelLoader::CreateTextures(aiMaterial* material, aiTextureType ai_type, Texture::Type type, std::string const& path) const
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i != material->GetTextureCount(ai_type); ++i)
	{
		aiString name;
		material->GetTexture(ai_type, i, &name);

		Texture texture(path.substr(0, path.find_last_of('/')) + "/" + name.C_Str(), type);
		textures.push_back(texture);
	}
	return textures;
}
