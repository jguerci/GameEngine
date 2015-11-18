#include "texture.h"

#include <SOIL\SOIL.h>
#include <iostream>

std::map<std::string, GLuint> Texture::textureCache;

GLuint Texture::GetTexture(const std::string& texturePath)
{
	auto it = textureCache.find(texturePath);

	if (it == textureCache.end()) 
	{
		GLuint textureID;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		textureID = SOIL_load_OGL_texture
			(
			texturePath.c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);

		if (textureID == 0)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
		}

		textureCache.insert(make_pair(texturePath, textureID));

		return textureID;
	}

	return it->second;
}