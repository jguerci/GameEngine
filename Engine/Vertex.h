#pragma once

#include <glm\glm.hpp>

using namespace glm;

struct Vertex 
{
	vec4 color;
	vec3 position;
	vec3 normal;
	vec2 texCoords;

	Vertex() : color(0, 0, 0, 0), position(0, 0, 0), normal(0, 0, 0), texCoords(0, 0) {}

	Vertex(const vec3& pos, const vec4& col = vec4(0, 0, 0, 0), 
		   const vec2& texCoord = vec2(0, 0), const vec3& normal = vec3(0, 0, 0)) :
		   position(pos), color(col), texCoords(texCoord), normal(normal) {}
};