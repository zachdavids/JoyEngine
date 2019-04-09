#pragma once

#include "GameObject.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Shader.h"

namespace Engine
{
	class Player : public GameObject
	{
	public:
		Player(ResourceManager const& resource_manager, glm::vec3 position);
		void Update();
		//TODO REPLACE WITH MODEL COMPONENT RENDER
		void Render() const;
	private:
		//TODO REPLACE WITH SOME SORT OF MODEL COMPONENT

		Shader* m_Shader;
		Model* m_Model;
	};
}

