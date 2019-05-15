#include "World.h"

World::World()
{
	initWorld();
}

World::~World()
{
}

void World::initWorld()
{
	blocks.resize(WORLD_SIZE, std::vector<bool>(WORLD_SIZE));
	blocks[1][1] = true;
}
