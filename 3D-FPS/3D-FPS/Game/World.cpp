#include "World.h"
#include "../Components/Draw/CubeComponent.h"
#include <fstream>
#include <string>
#include <iostream>

World::World(std::vector<GameObject*> &objects)
{
	initWorld(objects);
}

void World::initWorld(std::vector<GameObject*> &objects)
{
	blocks.resize(WORLD_SIZE, std::vector<bool>(WORLD_SIZE));
	
	readFile();

	for (auto x = 0; x < WORLD_SIZE; ++x)
		for (auto z = 0; z < WORLD_SIZE; ++z)
			if (blocks[x][z])
				setBlock(objects, x, z);
}

void World::readFile()
{
	std::ifstream file("Game/world.txt");
	if (!file.is_open())
		return;

	std::string line;
	auto x = 0, z = 0;
	while (getline(file, line))
	{
		z = 0;
		std::cout << line << std::endl;
		for (auto c : line)
			if (c == '1')
				blocks[x][z++] = true;
			else z++;
		x++;
	}
	file.close();
}

void World::setBlock(std::vector<GameObject *> &objects, const int x, const int z) const
{
	auto block = new GameObject();
	block->addComponent(new CubeComponent(1));
	block->position = { x - WORLD_SIZE / 2.0f + 0.5f, 0.5f, z - WORLD_SIZE / 2.0f + 0.5f };
	objects.push_back(block);
}

bool World::isWall(const int x, const int z)
{
	if (x < -WORLD_SIZE / 2 || z < -WORLD_SIZE / 2 || x >= WORLD_SIZE / 2 || z >= WORLD_SIZE / 2)
		return false;
	return blocks[x + WORLD_SIZE / 2][z + WORLD_SIZE / 2];
}
