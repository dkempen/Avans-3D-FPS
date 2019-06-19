#pragma once

#include <vector>
#include "Block.h"
#include "../Components/Base/GameObject.h"

class World
{
	const int WORLD_SIZE = 20;
	std::vector<std::vector<int>> worldBlocks;

	void initWorld(std::vector<GameObject *> &objects);
	void readFile();
	void setBlock(std::vector<GameObject *> &objects, int x, int z, Block::BlockType blockType) const;
	static Block::BlockType intToBlockType(int number);
public:
	World(std::vector<GameObject *> &objects);
	~World() = default;

	float getBlockHeight(int x, int z);
	void setOnRandomEmptyBlock(Vec3f &position) const;
};
