#include "SpriteShader.h"

SpriteShader::SpriteShader()
{
	Compile("SpriteVertex.vert", "SpriteFragment.frag");

	AddUniform("projection");
	AddUniform("view");
}

void SpriteShader::UpdateUniforms(const mat4& view, const mat4& projection)
{
	SetUniform("projection", projection);
	SetUniform("view", view);
}
