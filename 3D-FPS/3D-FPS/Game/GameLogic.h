#pragma once
#include <vector>
#include "World.h"

class GameLogic
{
	void initGame();
public:
	World *world;
	std::vector<GameObject *> objects;
	GameObject *player;

	GameLogic();
	~GameLogic();

	void draw();
	void update(float deltaTime);
};
