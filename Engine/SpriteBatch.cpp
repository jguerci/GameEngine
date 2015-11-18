#include "SpriteBatch.h"

#include <algorithm>

Sprite::Sprite(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec4& UV)
{
	texture = mat.textureID;
	depth = pos.z;

	topLeft.color     = mat.color;
	topRight.color	  = mat.color;
	bottomLeft.color  = mat.color;
	bottomRight.color = mat.color;
	
	topLeft.position     = vec3(pos.x, pos.y + size.y, 0.0f);
	topRight.position    = vec3(pos.x + size.x, pos.y + size.y, 0.0f);
	bottomLeft.position  = vec3(pos.x, pos.y, 0.0f);
	bottomRight.position = vec3(pos.x + size.x, pos.y, 0.0f);

	topLeft.texCoords     = vec2(UV.x, UV.y + UV.w);
	topRight.texCoords    = vec2(UV.x + UV.z, UV.y + UV.w);
	bottomLeft.texCoords  = vec2(UV.x, UV.y);
	bottomRight.texCoords = vec2(UV.x + UV.z, UV.y);
}

Sprite::Sprite(const glm::vec3& pos, const glm::vec2& size, const Material& mat, float angle, const glm::vec4& UV)
{
	texture = mat.textureID;
	depth = pos.z;

	glm::vec2 halfDims(size.x / 2.0f, size.y / 2.0f);

	glm::vec2 tl(-halfDims.x, halfDims.y);
	glm::vec2 bl(-halfDims.x, -halfDims.y);
	glm::vec2 br(halfDims.x, -halfDims.y);
	glm::vec2 tr(halfDims.x, halfDims.y);

	tl = RotatePoint(tl, angle) + halfDims;
	bl = RotatePoint(bl, angle) + halfDims;
	br = RotatePoint(br, angle) + halfDims;
	tr = RotatePoint(tr, angle) + halfDims;

	topLeft.color     = mat.color;
	topRight.color    = mat.color;
	bottomLeft.color  = mat.color;
	bottomRight.color = mat.color;

	topLeft.position     = vec3(pos.x + tl.x, pos.y + tl.y, 0.0f);
	topRight.position    = vec3(pos.x + tr.x, pos.y + tr.y, 0.0f);
	bottomLeft.position  = vec3(pos.x + bl.x, pos.y + bl.y, 0.0f);
	bottomRight.position = vec3(pos.x + br.x, pos.y + br.y, 0.0f);

	topLeft.texCoords     = vec2(UV.x, UV.y + UV.w);
	topRight.texCoords    = vec2(UV.x + UV.z, UV.y + UV.w);
	bottomLeft.texCoords  = vec2(UV.x, UV.y);
	bottomRight.texCoords = vec2(UV.x + UV.z, UV.y);
}

glm::vec2 Sprite::RotatePoint(const glm::vec2& pos, float angle) 
{
	glm::vec2 newv;
	newv.x = pos.x * cos(angle) - pos.y * sin(angle);
	newv.y = pos.x * sin(angle) + pos.y * cos(angle);
	return newv;
}

SpriteBatch::SpriteBatch()
{
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);

	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::Begin() {
	_renderBatches.clear();
	_sprites.clear();
}

void SpriteBatch::End() {
	_spritePointers.resize(_sprites.size());
	for (size_t i = 0; i < _sprites.size(); i++) {
		_spritePointers[i] = &_sprites[i];
	}

	std::stable_sort(_spritePointers.begin(), _spritePointers.end(), CompareTexture);
	CreateRenderBatches();
}

void SpriteBatch::Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec4& UV) {
	_sprites.emplace_back(pos, size, mat, UV);
}

void SpriteBatch::Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, float angle, const glm::vec4& UV) {
	_sprites.emplace_back(pos, size, mat, angle, UV);
}

void SpriteBatch::Draw(const glm::vec3& pos, const glm::vec2& size, const Material& mat, const glm::vec2& dir, const glm::vec4& UV) {
	const glm::vec2 right(1.0f, 0.0f);
	float angle = acos(glm::dot(right, dir));
	if (dir.y < 0.0f) angle = -angle;

	_sprites.emplace_back(pos, size, mat, angle, UV);
}

void SpriteBatch::RenderBatches() {
	glBindVertexArray(_vao);
	for (size_t i = 0; i < _renderBatches.size(); i++) {
		glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);

		glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}

void SpriteBatch::CreateRenderBatches() {
	std::vector <Vertex> vertices;
	vertices.resize(_spritePointers.size() * 6);

	if (_spritePointers.empty()) {
		return;
	}

	int offset = 0;
	int cv = 0;

	_renderBatches.emplace_back(offset, 6, _spritePointers[0]->texture);
	vertices[cv++] = _spritePointers[0]->topLeft;
	vertices[cv++] = _spritePointers[0]->bottomLeft;
	vertices[cv++] = _spritePointers[0]->bottomRight;
	vertices[cv++] = _spritePointers[0]->bottomRight;
	vertices[cv++] = _spritePointers[0]->topRight;
	vertices[cv++] = _spritePointers[0]->topLeft;
	offset += 6;

	for (size_t cg = 1; cg < _spritePointers.size(); cg++) {

		if (_spritePointers[cg]->texture != _spritePointers[cg - 1]->texture) {
			_renderBatches.emplace_back(offset, 6, _spritePointers[cg]->texture);
		}
		else {
			_renderBatches.back().numVertices += 6;
		}
		vertices[cv++] = _spritePointers[cg]->topLeft;
		vertices[cv++] = _spritePointers[cg]->bottomLeft;
		vertices[cv++] = _spritePointers[cg]->bottomRight;
		vertices[cv++] = _spritePointers[cg]->bottomRight;
		vertices[cv++] = _spritePointers[cg]->topRight;
		vertices[cv++] = _spritePointers[cg]->topLeft;
		offset += 6;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool SpriteBatch::CompareTexture(Sprite* a, Sprite* b) {
	return (a->texture < b->texture);
}