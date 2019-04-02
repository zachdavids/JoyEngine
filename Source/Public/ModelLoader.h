#pragma once

#include <string>

namespace Engine
{
	class ModelLoader
	{
	public:
		ModelLoader() = default;
		void Create(std::string const& path);

	private:
		void ProcessNode(aiNode * node, const aiScene * scene);
		ProcessMesh(aiMesh * mesh, const aiScene * scene)
	};
}

