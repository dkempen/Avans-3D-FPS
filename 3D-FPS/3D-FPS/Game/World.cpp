#include "World.h"
#include <fstream>
#include <string>
#include <iostream>
#include "../Components/Draw/TextureComponent.h"
#include "../DataManager.h"

World::World(std::vector<GameObject*> &objects)
{
	initWorld(objects);
}

void World::initWorld(std::vector<GameObject*> &objects)
{
	worldBlocks.resize(WORLD_SIZE, std::vector<int>(WORLD_SIZE));
	
	readFile();

	for (auto x = 0; x < WORLD_SIZE; ++x)
		for (auto z = 0; z < WORLD_SIZE; ++z)
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
		{
			switch (c)
			{
			case '1':
				worldBlocks[x][z] = 1;
				break;
			case '2':
				worldBlocks[x][z] = 2;
				break;
			default:;
			}
			z++;
		}
		x++;
	}
	file.close();
}

void World::setBlock(std::vector<GameObject *> &objects, const int x, const int z) const
{
	auto block = new GameObject();
	const auto blockType = convertToBlockType(worldBlocks[x][z]);

	auto blocks = DataManager::getInstance().blocks;
	const auto posOffset = blocks[blockType].posOffset;
	const auto size = blocks[blockType].size;

	block->addComponent(new TextureComponent(blockType));
	block->position = { posOffset.x + x + 0.0f, posOffset.y, posOffset.z + z + 0.0f };
	block->scale = { size.x, size.y, size.z };

	objects.push_back(block);
}

float World::getBlockHeight(const int x, const int z)
{
	if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE)
		return -1;

	const auto block = DataManager::getInstance().blocks[convertToBlockType(worldBlocks[x][z])];
	return block.size.y + block.posOffset.y;
}

Block::BlockType World::convertToBlockType(const int number)
{
	Block::BlockType blockType = {};
	switch (number)
	{
	case 0:
		blockType = Block::BlockType::FLOOR;
		break;
	case 1:
		blockType = Block::BlockType::CRATE;
		break;
	case 2:
		blockType = Block::BlockType::WALL;
		break;
	default:;
	}
	return blockType;
}
