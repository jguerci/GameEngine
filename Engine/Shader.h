#pragma once

#include <map>
#include <string>
#include <glm\glm.hpp>
#include <GL\glew.h>

using namespace glm;

class Shader
{
public:
	Shader();
	virtual ~Shader();

	void Compile(const std::string& vs, const std::string& fs);

	void AddUniform(const std::string& uniform);
	void SetUniform(const std::string& name, int value);
	void SetUniform(const std::string& name, float value);
	void SetUniform(const std::string& name, const vec3& value);
	void SetUniform(const std::string& name, const mat4& value);
	virtual void UpdateUniforms(const mat4& view, const mat4& projection);

	void Use();
	void Unuse();
private:
	void CompileShader(const std::string& name, GLuint id);

	GLuint program_ = 0;
	GLuint vertexShader_ = 0;
	GLuint fragmentShader_ = 0;
	std::map<std::string, GLint> uniforms_;
};