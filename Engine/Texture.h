#pragma once

#include <GL/glew.h>
#include <map>
#include <string>

class Texture
{
public:
	static GLuint GetTexture(const std::string& texturePath);
protected:
private:
	static std::map<std::string, GLuint> textureCache;
};

