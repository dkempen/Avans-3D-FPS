#pragma once
#include <vector>
#include "../Components/Base/GameObject.h"

class World
{
	const int WORLD_SIZE = 10;
	std::vector<std::vector<int>> blocks;

	void initWorld(std::vector<GameObject *> &objects);
	void readFile();
	void setBlock(std::vector<GameObject *> &objects, int x, int y, int type) const;
public:
	World(std::vector<GameObject *> &objects);
	~World() = default;

	bool isWall(int x, int z);
};
