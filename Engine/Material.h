#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>

using namespace glm;

struct Material
{
	GLuint textureID;
	vec4 color;

	Material(GLuint texture = -1, const vec4& color = vec4(1.0f, 1.0f, 1.0f, 1.0f)) :
		textureID(texture), color(color) {}
};