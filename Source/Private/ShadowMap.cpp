#include "ShadowMap.h"

#include <glad/glad.h>

Engine::ShadowMap::ShadowMap()
{

}

void Engine::ShadowMap::Create()
{
	GenerateCubeMap();
}

void Engine::ShadowMap::GenerateCubeMap()
{
	glGenFramebuffers(1, &m_CaptureFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_CaptureFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_CubeMap, 0);

    glGenTextures(1, &m_CubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMap);
	for (unsigned int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, 
			1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

