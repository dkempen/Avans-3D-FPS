#include "TextureManager.h"
#include <utility>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager::TextureManager()
: textureId(0), atlas("Resources/textures.png")
{
	loadTexture();
	blocks[TextureComponent::BlockType::CRATE] = getTileCoords(TextureComponent::BlockType::CRATE, 4, 1, 1);
	blocks[TextureComponent::BlockType::WALL] = getTileCoords(TextureComponent::BlockType::WALL, 0, 1, 2);
}

TextureManager::Block TextureManager::getTileCoords(const TextureComponent::BlockType block,
	const int tile, const int width, const int height) const
{
	const int col = tile % tileCount;
	const int row = floor(tile / tileCount);
	const auto x1 = static_cast<float>(col) / tileCount;
	const auto y1 = static_cast<float>(row) / tileCount;
	const auto x2 = static_cast<float>((col + width)) / tileCount;
	const auto y2 = static_cast<float>((row + height)) / tileCount;
	return Block({ x1, y1, x2, y2 });
}

void TextureManager::getBlockCoords(const TextureComponent::BlockType block, float& x1, float& y1, float& x2, float& y2)
{
	const auto b = blocks[block];
	x1 = b.x1;
	y1 = b.y1;
	x2 = b.x2;
	y2 = b.y2;
}

void TextureManager::loadTexture()
{
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int textureWidth, textureHeight, bpp;
	const auto imgData = stbi_load(atlas.c_str(), &textureWidth, &textureHeight, &bpp, 4);
	tileCount = 16;
	tileSize = textureHeight / tileCount;

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

GLint TextureManager::getTextureId() const
{
	return textureId;
}
