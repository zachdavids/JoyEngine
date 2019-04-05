#include "Shader.h"
#include "Tools.h"

#include <iostream>
#include <vector>
#include <glm/gtc/type_ptr.hpp>

const std::string Engine::Shader::m_Directory = "Resources/Shaders/";

Engine::Shader::Shader(std::string const& path) : Resource(m_Directory + path)
{
}

void Engine::Shader::Create()
{
	const std::string vertex = "Vertex.glsl";
	const std::string fragment = "Fragment.glsl";

	int vertex_id = LoadShader(m_Path + vertex, GL_VERTEX_SHADER);
	int fragment_id = LoadShader(m_Path + fragment, GL_FRAGMENT_SHADER);
	m_ID = Compile(vertex_id, fragment_id);
}

void Engine::Shader::Use() const
{
	glUseProgram(m_ID);
}

void Engine::Shader::SetMat4(std::string const& name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

int Engine::Shader::LoadShader(std::string const& path, GLuint type) const
{
	std::string code;
	Engine::Tools::ReadFile(&code, path);

	const char* vertex_code = code.c_str();
	GLuint shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &vertex_code, NULL);
	glCompileShader(shader_id);

	//TODO: Remove after release
	GLint status;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		GLint maxLength = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shader_id, maxLength, &maxLength, &infoLog[0]);

		for (unsigned int i = 0; i < infoLog.size(); i++)
		{
			std::cout << infoLog[i];
		}
		glDeleteProgram(shader_id);
	}
	return shader_id;
}

int Engine::Shader::Compile(GLuint vertex_id, GLuint fragment_id) const
{
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_id);
	glAttachShader(program_id, fragment_id);
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
	return program_id;
}
