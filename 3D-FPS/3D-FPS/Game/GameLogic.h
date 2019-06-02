#pragma once
#include <vector>
#include "World.h"
#include "../Texture/TextureManager.h"

class GameLogic
{
	World *world;
	std::vector<GameObject *> objects;
	GameObject *player;

	// TextureManager textureManager;
public:
	GameLogic();
	~GameLogic();

	void draw();
	void update(float deltaTime);

	GameObject *getPlayer() const;
};
