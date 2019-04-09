#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

const std::string Engine::Model::m_Directory = "Resources/Models/";

Engine::Model::Model(std::string const& path) : Resource(m_Directory + path)
{
}

void Engine::Model::Create()
{
	Assimp::Importer import;
	import.SetPropertyInteger(AI_CONFIG_PP_RVC_FLAGS, aiComponent_NORMALS);
	const aiScene* scene = import.ReadFile(m_Path, aiProcess_RemoveComponent | aiProcess_FixInfacingNormals | aiProcess_TransformUVCoords | aiProcessPreset_TargetRealtime_MaxQuality);
	ProcessNode(scene->mRootNode, scene);

	for (int i = 0; i != m_Meshes.size(); i++)
	{
		m_Meshes[i].Create();
	}
}

void Engine::Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i != node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
		ProcessTextures(scene->mMaterials[mesh->mMaterialIndex]);
	}
	for (unsigned int i = 0; i != node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

void Engine::Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices = CreateVertices(mesh);
	std::vector<unsigned int> indices = CreateIndices(mesh);

	m_Meshes.push_back(Mesh(vertices, indices));
}

std::vector<Engine::Vertex> Engine::Model::CreateVertices(aiMesh* mesh) const
{
	std::vector<Vertex> vertices;
	for (unsigned int i = 0; i != mesh->mNumVertices; ++i)
	{
		Vertex vertex;
		vertex.m_Position.x = mesh->mVertices[i].x;
		vertex.m_Position.y = mesh->mVertices[i].y;
		vertex.m_Position.z = -mesh->mVertices[i].z;

		vertex.m_UV.x = mesh->mTextureCoords[0][i].x;
		vertex.m_UV.y = mesh->mTextureCoords[0][i].y;

		vertex.m_Normal.x = mesh->mNormals[i].x;
		vertex.m_Normal.y = mesh->mNormals[i].y;
		vertex.m_Normal.z = mesh->mNormals[i].z;

		vertex.m_Tangent.x = mesh->mTangents[i].x;
		vertex.m_Tangent.y = mesh->mTangents[i].y;
		vertex.m_Tangent.z = mesh->mTangents[i].z;

		vertex.m_Bitangent.x = mesh->mBitangents[i].x;
		vertex.m_Bitangent.y = mesh->mBitangents[i].y;
		vertex.m_Bitangent.z = mesh->mBitangents[i].z;

		vertices.push_back(vertex);
	}
	return vertices;
}

std::vector<unsigned int> Engine::Model::CreateIndices(aiMesh* mesh) const
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

void Engine::Model::ProcessTextures(aiMaterial* material)
{
	std::vector<Texture> textures;
	std::vector<Texture> diffuse = CreateTextures(material, aiTextureType_DIFFUSE, Texture::Type::kDiffuse);
	textures.insert(std::end(textures), std::begin(diffuse), std::end(diffuse));

	std::vector<Texture> specular = CreateTextures(material, aiTextureType_SPECULAR, Texture::Type::kSpecular);
	textures.insert(std::end(textures), std::begin(specular), std::end(specular));

	std::vector<Texture> normal = CreateTextures(material, aiTextureType_NORMALS, Texture::Type::kNormals);
	textures.insert(std::end(textures), std::begin(normal), std::end(normal));

	std::vector<Texture> height = CreateTextures(material, aiTextureType_HEIGHT, Texture::Type::kHeight);
	textures.insert(std::end(textures), std::begin(height), std::end(height));

	m_Textures.push_back(textures);
}

std::vector<Engine::Texture> Engine::Model::CreateTextures(aiMaterial* material, aiTextureType ai_type, Texture::Type type) const
{
	//TODO CHECK FOR PRE-LOADED TEXTURES
	std::vector<Texture> textures;
	for (unsigned int i = 0; i != material->GetTextureCount(ai_type); ++i)
	{
		aiString name;
		material->GetTexture(ai_type, i, &name);

		Texture texture(m_Path.substr(0, m_Path.find_last_of('/')) + "/" + name.C_Str(), type);
		texture.Create();
		textures.push_back(texture);
	}
	return textures;
}
