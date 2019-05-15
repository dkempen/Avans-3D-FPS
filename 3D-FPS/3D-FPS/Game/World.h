#pragma once
#include <vector>

class World
{
	const int WORLD_SIZE = 5;
	std::vector<std::vector<bool>> blocks;

	void initWorld();
public:
	World();
	~World();
};
