#include "SpriteSheet.h"


SpriteSheet::SpriteSheet()
{
	dimensions_ = glm::vec2(1, 1);
}

SpriteSheet::SpriteSheet(const glm::ivec2& tileDims)
{
	dimensions_ = tileDims;
}


SpriteSheet::~SpriteSheet()
{
}

glm::vec4 SpriteSheet::GetUVs(int index)
{
	int xTile = index % dimensions_.x;
	int yTile = index / dimensions_.x;

	glm::vec4 uvs;
	uvs.x = xTile / (float)dimensions_.x;
	uvs.y = yTile / (float)dimensions_.y;
	uvs.z = 1.0f / dimensions_.x;
	uvs.w = 1.0f / dimensions_.y;

	return uvs;
}