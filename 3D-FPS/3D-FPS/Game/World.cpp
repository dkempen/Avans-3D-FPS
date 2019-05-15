#include "World.h"
#include "../Components/CubeComponent.h"

World::World(std::vector<GameObject*> &objects)
{
	initWorld(objects);
}

World::~World()
{
}

void World::initWorld(std::vector<GameObject*> &objects)
{
	blocks.resize(WORLD_SIZE, std::vector<GameObject *>(WORLD_SIZE));
	GameObject *block = new GameObject();
	block->addComponent(new CubeComponent(1));
	block->position = Vec3f(1.5, 0.5, 1.5);
	blocks[1][1] = block;
	objects.push_back(block);
}

bool World::isWall(int x, int y)
{
	return blocks[x][y];
}
