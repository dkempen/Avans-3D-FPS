#pragma once
#include <vector>
#include "../Components/Base/GameObject.h"

class World
{
	const int WORLD_SIZE = 5;
	std::vector<std::vector<GameObject *>> blocks;

	void initWorld(std::vector<GameObject*> &objects);
public:
	World(std::vector<GameObject*> &objects);
	~World();

	bool isWall(int x, int y);
};
