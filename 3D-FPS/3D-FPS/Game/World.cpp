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
	blocks.resize(WORLD_SIZE, std::vector<int>(WORLD_SIZE));
	
	readFile();

	for (auto x = 0; x < WORLD_SIZE; ++x)
		for (auto z = 0; z < WORLD_SIZE; ++z)
			setBlock(objects, x, z, blocks[x][z]);
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
		{
			switch (c)
			{
			case '1':
				blocks[x][z] = 1;
				break;
			case '2':
				blocks[x][z] = 2;
				break;
			default:;
			}
			z++;
		}
		x++;
	}
	file.close();
}

void World::setBlock(std::vector<GameObject *> &objects, const int x, const int z, int type) const
{
	auto block = new GameObject();
	switch (type)
	{
	case 1:
		block->addComponent(new CubeComponent(1));
		break;
	case 2:
		block->addComponent(new CubeComponent(1));
		block->scale = { 1, 3, 1 };
		break;
	default:;
	}
	block->position = { x + 0.5f, 0.5f, z + 0.5f };
	objects.push_back(block);
}

bool World::isWall(const int x, const int z)
{
	if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE)
		return false;
	return blocks[x][z];
}
