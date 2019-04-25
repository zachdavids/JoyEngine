#pragma once

namespace Engine
{
	class ShadowMap
	{
	public:
		ShadowMap();
		void Create();
	private:
		unsigned int m_CaptureFBO;
		unsigned int m_CubeMap;
		void GenerateCubeMap();
	};
}

