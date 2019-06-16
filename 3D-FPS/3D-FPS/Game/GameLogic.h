#pragma once
#include <vector>
#include "World.h"

class GameLogic
{
	World *world;
	std::vector<GameObject *> objects;
	GameObject *player;
public:
	GameLogic();
	~GameLogic();

	void init();
	void draw();
	void update(float deltaTime);

	GameObject *getPlayer() const;
};
