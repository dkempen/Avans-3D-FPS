#pragma once
#include <vector>
#include "../Components/Base/GameObject.h"
#include "Block.h"

class World
{
	const int WORLD_SIZE = 10;
	std::vector<std::vector<int>> worldBlocks;

	void initWorld(std::vector<GameObject *> &objects);
	void readFile();
	void setBlock(std::vector<GameObject *> &objects, int x, int y, Block::BlockType type) const;
	static Block::BlockType intToBlockType(int number);
public:
	World(std::vector<GameObject *> &objects);
	~World() = default;

	float getBlockHeight(int x, int z);

};
