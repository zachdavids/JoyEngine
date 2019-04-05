#pragma once

namespace Engine
{
	class GameObject
	{
	public:
		virtual void Create() = 0;
		virtual void Update() = 0;
	protected:
		int m_ID;
	};
}

