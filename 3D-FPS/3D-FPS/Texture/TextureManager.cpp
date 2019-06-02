#include "TextureManager.h"
#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager::TextureManager(const GLuint textureId, std::string atlas)
: textureId(textureId), atlas(std::move(atlas))
{
}

TextureManager::~TextureManager() = default;

void TextureManager::loadTexture()
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int textureWidth, textureHeight, bpp;
	const auto imgData = stbi_load(atlas.c_str(), &textureWidth, &textureHeight, &bpp, 4);

	glTexImage2D(GL_TEXTURE_2D,
		0,				//level
		GL_RGBA,		//internal format
		textureWidth,	//width
		textureHeight,	//height
		0,				//border
		GL_RGBA,		//data format
		GL_UNSIGNED_BYTE,//data type
		imgData);		//data
	stbi_image_free(imgData);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
