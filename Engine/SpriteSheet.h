#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class SpriteSheet
{
public:
	SpriteSheet();
	SpriteSheet(const glm::ivec2& tileDims);
	~SpriteSheet();

	glm::vec4 GetUVs(int index);
	inline void SetDimensions(const glm::ivec2& dim) { dimensions_ = dim; }
private:
	glm::ivec2 dimensions_;
};

