#include "Skybox.h"
#include "stb_image.h"
#include "Shader.h"
#include "Model.h"

#include <iostream>

#include <glad/glad.h>

Engine::Skybox::Skybox(ResourceManager const& resource_manager) :
	m_Shader(resource_manager.GetResource<Shader>("SkyboxShader")),
	m_Model(resource_manager.GetResource<Model>("Skybox"))
{
}

void Engine::Skybox::Create()
{
	const std::string directory = "Resources/Textures/Skybox/";
	std::vector<std::string> paths
	{
		directory + "right.jpg",
		directory + "left.jpg",
		directory + "top.jpg",
		directory + "bottom.jpg",
		directory + "front.jpg",
		directory + "back.jpg"
	};

	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	stbi_set_flip_vertically_on_load(false);

	int width;
	int height;
	int components;
	for (int i = 0; i != paths.size(); i++)
	{
		unsigned char *data = stbi_load(paths[i].c_str(), &width, &height, &components, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Engine::Skybox::Render()
{
	m_Shader->Use();
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(m_Model->GetMeshes()[0].GetVAO());
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_ID);
	glDrawElements(GL_TRIANGLES, m_Model->GetMeshes()[0].GetSize(), GL_UNSIGNED_INT, 0);
	glDepthFunc(GL_LESS);
}
