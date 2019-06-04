#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Extern/stb_image.h"

TextureManager::TextureManager()
: textureId(0), atlas("Resources/textures.png")
{
}

void TextureManager::initBlockTextures(std::map<Block::BlockType, Block> &blocks)
{
	loadTexture();

	getTileCoords(blocks[Block::BlockType::FLOOR], 153, 1, 1);
	getTileCoords(blocks[Block::BlockType::CRATE], 4, 1, 1);
	getTileCoords(blocks[Block::BlockType::HIGH_CRATE], 192, 1, 2);
	getTileCoords(blocks[Block::BlockType::WALL], 162, 1, 4);
	getTileCoords(blocks[Block::BlockType::CEILING], 6, 1, 1);
}

void TextureManager::getTileCoords(Block &block, const int tile, const int width, const int height) const
{
	const auto col = tile % tileCount;
	const auto row = static_cast<int>(floor(tile / tileCount));

	block.x1 = static_cast<float>(col) / tileCount;
	block.y1 = static_cast<float>(row) / tileCount;
	block.x2 = static_cast<float>((col + width)) / tileCount;
	block.y2 = static_cast<float>((row + height)) / tileCount;
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
