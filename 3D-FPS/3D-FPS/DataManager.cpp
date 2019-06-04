#include "DataManager.h"

DataManager::DataManager()
{
	initBlocks();
}

void DataManager::initBlocks()
{
	// Create all blocks
	blocks[Block::BlockType::FLOOR];
	blocks[Block::BlockType::CRATE];
	blocks[Block::BlockType::WALL];

	// Init position and dimensions
	blocks[Block::BlockType::FLOOR].posOffset = { 0, -1, 0 };
	blocks[Block::BlockType::WALL].size = { 1, 2, 1 };
}

void DataManager::getBlockCoords(const Block::BlockType block, float& x1, float& y1, float& x2, float& y2)
{
	const auto b = blocks[block];
	x1 = b.x1;
	y1 = b.y1;
	x2 = b.x2;
	y2 = b.y2;
}
