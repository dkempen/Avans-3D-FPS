#pragma once

#include <GL/freeglut.h>
#include <string>
#include <vector>
#include <map>
#include "../Game/Block.h"

class TextureManager
{
	int tileCount;
	int tileSize;

	void getTileCoords(Block &block, int tile, int width, int height) const;
public:
	std::string atlas;
	GLuint textureId;

	TextureManager();

	void initBlockTextures(std::map<Block::BlockType, Block> &blocks);
	GLint getTextureId() const;
};
