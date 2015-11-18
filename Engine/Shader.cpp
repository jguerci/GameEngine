#include "Shader.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "GameErrors.h"

static std::string ShaderFileToString(const std::string& fileName);

Shader::Shader()
{
	program_ = glCreateProgram();

	if (program_ == 0) 
	{
		GameError("glCreateProgram failed");
	}
}

Shader::~Shader()
{
	glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
	glDeleteProgram(program_);
}

void Shader::Use()
{
	glUseProgram(program_);
}

void Shader::Unuse()
{
	glUseProgram(0);
}

void Shader::Compile(const std::string& vs, const std::string& fs)
{
	std::string vertexSource = ShaderFileToString(vs);
	std::string fragmentSource = ShaderFileToString(fs);

	const char* vsSource = vertexSource.c_str();
	const char* fsSource = fragmentSource.c_str();

	vertexShader_ = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader_ == 0)
	{
		GameError("Failed to create vertex shader");
	}

	fragmentShader_ = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader_ == 0)
	{
		GameError("Failed to create fragment shader_");
	}

	glShaderSource(vertexShader_, 1, &vsSource, 0);
	CompileShader("Vertex", vertexShader_);

	glShaderSource(fragmentShader_, 1, &fsSource, 0);
	CompileShader("Fragment", fragmentShader_);

	glLinkProgram(program_);
}

void Shader::AddUniform(const std::string& uniform)
{
	GLint location = glGetUniformLocation(program_, uniform.c_str());
	uniforms_.emplace(uniform, location);
}

void Shader::UpdateUniforms(const mat4& view, const mat4& projection)
{

}

void Shader::SetUniform(const std::string& name, int value)
{
	glUniform1i(uniforms_.at(name), value);
}

void Shader::SetUniform(const std::string& name, float value)
{
	glUniform1f(uniforms_.at(name), value);
}

void Shader::SetUniform(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(uniforms_.at(name), 1, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(uniforms_.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CompileShader(const std::string& name, GLuint id)
{
	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
		glDetachShader(program_, id);
		glDeleteShader(id);

		std::printf("%s\n", &(infoLog[0]));
		GameError(name + " failed to compile");
	}

	glAttachShader(program_, id);
}

static std::string ShaderFileToString(const std::string& fileName)
{
	std::ifstream file("Shaders/" + fileName, std::ios::binary);
	if (file.fail()) 
	{
		perror(fileName.c_str());
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	return buffer.str();
}