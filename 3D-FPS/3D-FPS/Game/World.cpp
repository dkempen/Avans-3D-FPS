#include "World.h"
#include <fstream>
#include <string>
#include "../Components/Draw/TextureComponent.h"
#include "../Data/DataManager.h"

World::World(std::vector<GameObject*> &objects)
{
	initWorld(objects);
}

void World::initWorld(std::vector<GameObject*> &objects)
{
	worldBlocks.resize(WORLD_SIZE, std::vector<int>(WORLD_SIZE));

	readFile();

	// Create floor and ceiling blocks
	for (auto x = 0; x < WORLD_SIZE; ++x)
		for (auto z = 0; z < WORLD_SIZE; ++z)
		{
			// Block
			setBlock(objects, x, z, Block::BlockType::NONE);
			// Ceiling
			setBlock(objects, x, z, Block::BlockType::CEILING);
		}
}

void World::readFile()
{
	// Open the world file
	std::ifstream file("Game/world.txt");
	if (!file.is_open())
		return;

	// Read the contents and place it in a 2D vector
	std::string line;
	auto x = 0, z = 0;
	while (getline(file, line))
	{
		for (auto c : line)
			worldBlocks[x][z++] = c - '0';
		z = 0;
		x++;
	}
	file.close();
}

// Create a textured block object for a given place in the world
void World::setBlock(std::vector<GameObject *> &objects, const int x, const int z, Block::BlockType blockType) const
{
	if (blockType == Block::BlockType::NONE)
		blockType = intToBlockType(worldBlocks[x][z]);

	auto block = new GameObject();

	auto blocks = DataManager::getInstance().blocks;
	const auto posOffset = blocks[blockType].posOffset;
	const auto size = blocks[blockType].size;

	block->addComponent(new TextureComponent(blockType, "atlas"));
	block->position = { posOffset.x + x + 0.0f, posOffset.y, posOffset.z + z + 0.0f };
	block->scale = { size.x, size.y, size.z };

	objects.push_back(block);
}

// Gets the block height on a particular location for collision detection
float World::getBlockHeight(const int x, const int z)
{
	if (x < 0 || z < 0 || x >= WORLD_SIZE || z >= WORLD_SIZE)
		return -1;

	const auto block = DataManager::getInstance().blocks[intToBlockType(worldBlocks[x][z])];
	return block.size.y + block.posOffset.y;
}

// Sets the position to an empty block in the world, meaning no wall or crate is present
void World::setOnRandomEmptyBlock(Vec3f &position) const
{
	while (true)
	{
		const auto x = rand() % WORLD_SIZE;
		const auto z = rand() % WORLD_SIZE;
		if (worldBlocks[x][z] == 0)
		{
			position = { x + 0.5f, 0, z + 0.5f };
			return;
		}
	}
}

Block::BlockType World::intToBlockType(const int number)
{
	return static_cast<Block::BlockType>(number);
}
