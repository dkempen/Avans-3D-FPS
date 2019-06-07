#pragma once
#include "TextureManager.h"
#include "../Game/GameLogic.h"

class DataManager
{
	// Private singleton constructor
	DataManager();

	void initBlocks();
public:
	// Data members
	TextureManager textureManager;
	std::map<Block::BlockType, Block> blocks;

	// Returns the singleton of this data class
	static DataManager &getInstance()
	{
		static DataManager instance;
		return instance;
	}

	// Make sure there is no public constructor and copy
	DataManager(DataManager const &) = delete;
	void operator=(DataManager const &) = delete;

	void getBlockCoords(Block::BlockType block, float& x1, float& y1, float& x2, float& y2);
};
