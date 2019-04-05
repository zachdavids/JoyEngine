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
	protected:
		int m_ID;
		Transform m_Transform;
		GameObject* m_Parent = nullptr;
		std::vector<GameObject*> m_Children;
	};
}

