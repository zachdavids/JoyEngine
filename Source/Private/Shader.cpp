#include "Shader.h"
#include "Tools.h"

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>

const std::string Engine::Shader::m_Directory = "Resources/Shaders/";

Engine::Shader::Shader(std::string const& path) : 
	Resource(m_Directory + path)
{
}

void Engine::Shader::Create()
{
	for (const auto& file : std::filesystem::directory_iterator(m_Path))
	{
		LoadShader(file.path().string());
	}
	
	Compile();
}

void Engine::Shader::Use() const
{
	glUseProgram(m_ID);
}

void Engine::Shader::SetInt(std::string const& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Engine::Shader::SetFloat(std::string const& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Engine::Shader::SetVec3(std::string const& name, glm::vec3 const& value) const
{
	glUniform3fv(glGetUniformLocation(m_ID, name.c_str()), 1, glm::value_ptr(value));
}

void Engine::Shader::SetMat4(std::string const& name, glm::mat4 const& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Engine::Shader::LoadShader(std::string const& path)
{
	std::string code;
	Engine::Tools::ReadFile(&code, path);
	const char* stage_code = code.c_str();

	GLuint stage_id;
	if (path.find("Vertex") != std::string::npos)
	{
		stage_id = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (path.find("Fragment") != std::string::npos)
	{
		stage_id = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (path.find("TessEval") != std::string::npos)
	{
		stage_id = glCreateShader(GL_TESS_EVALUATION_SHADER);
	}
	else if (path.find("TessControl") != std::string::npos)
	{
		stage_id = glCreateShader(GL_TESS_CONTROL_SHADER);
	}

	glShaderSource(stage_id, 1, &stage_code, NULL);
	glCompileShader(stage_id);

	//TODO: Remove after release
	GLint status;
	glGetShaderiv(stage_id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetProgramiv(stage_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(stage_id, maxLength, &maxLength, &infoLog[0]);

		for (unsigned int i = 0; i < infoLog.size(); i++)
		{
			std::cout << infoLog[i];
		}
		glDeleteProgram(stage_id);
	}
	m_ShaderStages.push_back(stage_id);
}

void Engine::Shader::Compile()
{
	GLuint program_id = glCreateProgram();
	for (GLuint stage : m_ShaderStages)
	{
		glAttachShader(program_id, stage);
	}
	glLinkProgram(program_id);

	GLint status;
	glGetProgramiv(program_id, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program_id, maxLength, &maxLength, &infoLog[0]);

		for (unsigned int i = 0; i < infoLog.size(); i++) {
			std::cout << infoLog[i];
		}
		glDeleteProgram(program_id);
	}
	m_ID = program_id;
}
