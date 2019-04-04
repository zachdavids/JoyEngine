#pragma once

#include "Actor.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Shader.h"

namespace Engine
{
	class Player : public Actor
	{
	public:
		Player(ResourceManager const& resource_manager);
		void Create();
		void Update();
		//TODO REPLACE WITH MODEL COMPONENT RENDER
		void Render();
	private:
		//TODO REPLACE WITH SOME SORT OF MODEL COMPONENT
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<Model> m_Model;
	};
}

