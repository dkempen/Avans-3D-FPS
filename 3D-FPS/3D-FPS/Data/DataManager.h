#pragma once
#include "TextureManager.h"
#include "../Game/GameLogic.h"
#include "../Math/Graphics.h"

class DataManager
{
	// Private singleton constructor
	DataManager();

	void initBlocks();
public:
	// Data members
	TextureManager textureManager;
	std::map<Block::BlockType, Block> blocks;

	// Storage for all game meshes and textures
	std::map<std::string, Graphics::Mesh> meshes;
	std::map<std::string, uint16_t> textures;

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
	void initModels();
	Graphics::Mesh getMesh(const std::string& mesh);
	uint16_t getTexture(const std::string& texture);
};
