#include "World.h"
#include "../Components/Draw/CubeComponent.h"

World::World(std::vector<GameObject*> &objects)
{
	initWorld(objects);
}

World::~World()
{
}

void World::initWorld(std::vector<GameObject*> &objects)
{
	blocks.resize(WORLD_SIZE, std::vector<bool>(WORLD_SIZE));
	GameObject *block = new GameObject();
	block->addComponent(new CubeComponent(1));
	block->position = { 1.5, 0.5, 1.5 };
	objects.push_back(block);
	blocks[1][1] = block;

	GameObject *block2 = new GameObject();
	block2->addComponent(new CubeComponent(1));
	block2->position = { 2.5, 0.5, 2.5 };
	objects.push_back(block2);
	blocks[2][2] = block2;
}

bool World::isWall(int x, int z)
{
	if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE)
		return false;
	return blocks[x][z];
}
