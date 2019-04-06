#pragma once

#include "Transform.h"

#include <memory>
#include <vector>

namespace Engine
{
	class GameObject
	{
	public:
		virtual void Update();
		void AddChild(GameObject* child);
		void AttachTo(GameObject* parent);
		GameObject* m_Parent = nullptr;
		Transform m_Transform;
	protected:
		int m_ID;


		std::vector<GameObject*> m_Children;
	};
}

