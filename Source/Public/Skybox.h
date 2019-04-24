#pragma once

#include "ResourceManager.h"
#include "Shader.h"
#include "Model.h"

#include <string>
#include <vector>

namespace Engine
{
	class Skybox
	{
	public:
		Skybox(ResourceManager const& resource_manager);
		void Create();
		void Render();
		unsigned int GetHDRTexture() const { return m_HDRTexture.GetID(); }
		unsigned int GetCubeMap() const { return m_CubeMap; }
		unsigned int GetIraddianceMap() const { return m_IrradianceMap; }
		unsigned int GetPrefilterMap() const { return m_PrefilterMap; }
		unsigned int GetBRDFMap() const { return m_BRDFMap; }
	private:
		unsigned int m_CubeMap;
		unsigned int m_IrradianceMap;
		unsigned int m_PrefilterMap;
		unsigned int m_BRDFMap;
		unsigned int m_CaptureFBO;
		unsigned int m_CaptureRBO;
	
		static const std::string m_Directory;
		glm::mat4 m_Projection;
		glm::mat4 m_CaptureViews[6];
		Shader* m_Shader;
		Shader* m_ConversionShader;
		Shader* m_IrradianceShader;
		Shader* m_PrefilterShader;
		Shader* m_BRDFShader;
		Model* m_SkyboxModel;
		Model* m_Quad;
		Texture m_HDRTexture;
		void GenerateCubemap();
		void GenerateIrradianceMap();
		void GeneratePrefilterMap();
		void GenerateBRDF();
	};
}

