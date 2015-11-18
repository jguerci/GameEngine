/* Modification of Ben Arnold's SpriteBatch class */

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

#include "Vertex.h"
#include "Material.h"

class Sprite {
public:
	Sprite(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec4& UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	Sprite(const glm::vec3& pos, const glm::vec2& size, const Material& mat, float angle, const glm::vec4& UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	GLuint texture;
	float depth;

	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
private:
	glm::vec2 RotatePoint(const glm::vec2& pos, float angle);
};

class RenderBatch {
public:
	RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset),
		numVertices(NumVertices), texture(Texture) {
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void Begin();
	void End();

	void Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec4& UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, float angle, const glm::vec4& UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	void Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec2& dir, const glm::vec4& UV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	void RenderBatches();

private:
	void CreateRenderBatches();
	static bool CompareTexture(Sprite* a, Sprite* b);

	GLuint _vbo = 0;
	GLuint _vao = 0;

	std::vector<Sprite*> _spritePointers;
	std::vector<Sprite> _sprites;
	std::vector<RenderBatch> _renderBatches;
};