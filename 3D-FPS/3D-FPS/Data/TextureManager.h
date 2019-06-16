#pragma once

#include <GL/freeglut.h>
#include <map>
#include "../Game/Block.h"

class TextureManager
{
	int tileCount;

	void getTileCoords(Block &block, int tile, int width, int height) const;
public:
	TextureManager();

	void initBlockTextures(std::map<Block::BlockType, Block> &blocks) const;
	GLint getTextureId() const;
};
