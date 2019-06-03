#pragma once
#include <GL/freeglut.h>
#include <string>
#include <vector>
#include "../Components/Draw/TextureComponent.h"
#include <map>

class TextureManager
{
	union Block
	{
		struct
		{
			float x1, y1, x2, y2;
		};
		float t[4]{};
	};
	std::map<TextureComponent::BlockType, Block> blocks;

	GLuint textureId;
	std::string atlas;
	int tileCount;
	int tileSize;

	// Private singleton constructor
	TextureManager();

	Block getTileCoords(TextureComponent::BlockType block, int tile, int width, int height) const;

	void loadTexture();
public:
	// Returns the singleton of this data class
	static TextureManager &getInstance()
	{
		static TextureManager instance;
		return instance;
	}

	// Make sure there is no public constructor and copy
	TextureManager(TextureManager const &) = delete;
	void operator=(TextureManager const &) = delete;

	GLint getTextureId() const;
	void getBlockCoords(TextureComponent::BlockType block, float& x1, float& y1, float& x2, float& y2);
};
