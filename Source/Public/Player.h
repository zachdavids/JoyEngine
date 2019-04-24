#pragma once

#include "GameObject.h"
#include "Shader.h"
#include "Model.h"

namespace Engine
{
	class Player : public GameObject
	{
	public:
		Player(glm::vec3 position);
		void Update();
		//TODO REPLACE WITH MODEL COMPONENT RENDER
		void Render() const;
	private:
		Shader* m_Shader;
		Model* m_Model;
	};
}

