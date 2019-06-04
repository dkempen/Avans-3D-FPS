#include "World.h"
#include <fstream>
#include <string>
#include <iostream>
#include "../Components/Draw/TextureComponent.h"

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
	case 0:
		block->addComponent(new TextureComponent(TextureComponent::BlockType::FLOOR));
		block->position = { 0.0f, -1.0f, 0.0f };
		break;
	case 1:
		block->addComponent(new TextureComponent(TextureComponent::BlockType::CRATE));
		break;
	case 2:
		block->addComponent(new TextureComponent(TextureComponent::BlockType::WALL));
		block->scale = { 1, 2, 1 };
		break;
	default:;
	}
	block->position = { 
		block->position.x + x + 0.0f,
		block->position.y + 0.0f,
		block->position.z + z + 0.0f };
	objects.push_back(block);
}

float World::getBlockHeight(const int x, const int z)
{
	if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE)
		return -1;

	// TODO: Move block to separate class
	float blockHeight;
	switch (blocks[x][z])
	{
	case 0:
		blockHeight = 0;
		break;
	case 1:
		blockHeight = 1;
		break;
	case 2:
		blockHeight = 2;
		break;
	default:
		blockHeight = -1;
		break;
	}
	return blockHeight;
}
