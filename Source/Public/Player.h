#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Model.h"
#include "Camera.h"

namespace Engine
{
	class Player : public GameObject
	{
	public:
		Player() = default;
		Player(glm::vec3 position);
		void Create();
		void Update();
		//TODO REPLACE WITH MODEL COMPONENT RENDER
		void Render(Camera const& camera) const;
	private:
		Shader* m_Shader;
		Model* m_Model;
	};
}

