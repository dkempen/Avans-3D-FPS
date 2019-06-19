#pragma once
#include <vector>
#include "World.h"

class GameLogic
{
	World *world;
	std::vector<GameObject *> objects;
	GameObject *player;
	GameObject *bullet;

	float spawnCounter;

	static float degreeToRad(float degree);
public:
	GameLogic();
	~GameLogic();

	void init();
	void draw();
	void update(float deltaTime);

	GameObject *getPlayer() const;
	void spawnBullet();
	void handleBullets();
	void spawnAI();
	void handleAI(float deltaTime);
	std::vector<GameObject*> getObjects() const;
};
