#pragma once

#include "Shader.h"

class SpriteShader : public Shader
{
public:
	SpriteShader();

	void UpdateUniforms(const mat4& view, const mat4& projection);
protected:
private:
};

