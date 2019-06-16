#include "TextureManager.h"
#include "../Util/TextureLoader.h"

TextureManager::TextureManager()
	: textureId(2), atlas("Resources/Atlas/atlas.png"), tileCount(16), tileSize(16)
{
}

void TextureManager::initBlockTextures(std::map<Block::BlockType, Block> &blocks)
{
	textureId = TextureLoader::addTexture(atlas, textureId);

	getTileCoords(blocks[Block::BlockType::FLOOR], 153, 1, 1);
	getTileCoords(blocks[Block::BlockType::CRATE], 4, 1, 1);
	getTileCoords(blocks[Block::BlockType::HIGH_CRATE], 192, 1, 2);
	getTileCoords(blocks[Block::BlockType::WALL], 0, 1, 4);
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

GLint TextureManager::getTextureId() const
{
	return textureId;
}
