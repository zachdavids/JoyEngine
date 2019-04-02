#include "ModelLoader.h"

void Engine::ModelLoader::Create(std::string const& path)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	directory_ = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}
