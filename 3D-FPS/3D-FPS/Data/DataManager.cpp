#include "DataManager.h"
#include "../Util/ObjectLoader.h"
#include "../Util/TextureLoader.h"

DataManager::DataManager() = default;

void DataManager::init()
{
	initBlocks();
	initModels();
	textureManager.initBlockTextures(blocks);
}

void DataManager::initBlocks()
{
	// Create all blocks
	blocks[Block::BlockType::FLOOR];
	blocks[Block::BlockType::CRATE];
	blocks[Block::BlockType::HIGH_CRATE];
	blocks[Block::BlockType::WALL];
	blocks[Block::BlockType::CEILING];

	// Init position and dimensions
	blocks[Block::BlockType::FLOOR].posOffset = { 0, -1, 0 };
	blocks[Block::BlockType::HIGH_CRATE].size = { 1, 2, 1 };
	blocks[Block::BlockType::WALL].size = { 1, 4, 1 };
	blocks[Block::BlockType::CEILING].posOffset = { 0, 4, 0 };
}

void DataManager::getBlockCoords(const Block::BlockType block, float& x1, float& y1, float& x2, float& y2)
{
	const auto b = blocks[block];
	x1 = b.x1;
	y1 = b.y1;
	x2 = b.x2;
	y2 = b.y2;
}

void DataManager::initModels()
{
	textures["atlas"] = TextureLoader::addTexture("Resources/Atlas/atlas.png", textures.size());

	textures["weapon"] = TextureLoader::addTexture("Resources/Weapon/weapon.png", textures.size());
	meshes["weapon"] = ObjLoader::loadObj("Resources/Weapon/weapon.obj");

	meshes["bullet"] = ObjLoader::loadObj("Resources/Bullet/bullet.obj");

	textures["enemy"] = TextureLoader::addTexture("Resources/Enemy/enemy.png", textures.size());
	meshes["enemy"] = ObjLoader::loadObj("Resources/Enemy/enemy.obj");
}

Graphics::Mesh &DataManager::getMesh(const std::string& mesh)
{
	return meshes[mesh];
}

uint16_t &DataManager::getTexture(const std::string& texture)
{
	return textures[texture];
}
