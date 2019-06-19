#include "GameLogic.h"
#include "../Components/Base/GameObject.h"
#include "../Components/Control/PlayerComponent.h"
#include "../Components/Physics/CollisionComponent.h"
#include "../Components/Draw/ModelComponent.h"
#include "../Components/Other/WeaponComponent.h"
#include "../Components/Other/BulletComponent.h"
#include <corecrt_math_defines.h>
#include "../Components/Control/AIComponent.h"

GameLogic::GameLogic() = default;

void GameLogic::init()
{
	// Init world
	world = new World(objects);

	// Create player object
	player = new GameObject();
	player->position.x = 5;
	player->position.z = 5;
	player->addComponent(new PlayerComponent(*player));
	player->addComponent(new CollisionComponent());
	objects.push_back(player);

	// Create weapon object
	auto weapon = new GameObject();
	weapon->position = { 0.5f, -0.5f, -1 };
	weapon->rotation = { 0, 90, 180 };
	weapon->scale = { 0.5f, 0.5f, 0.5f };
	weapon->addComponent(new ModelComponent("weapon", true));
	weapon->addComponent(new WeaponComponent());
	objects.push_back(weapon);
}

GameLogic::~GameLogic() = default;

void GameLogic::draw()
{
	for (auto &o : objects)
		o->draw();
}

void GameLogic::update(const float deltaTime)
{
	handleAI(deltaTime);
	handleBullets();

	for (auto &o : objects)
		o->update(*this, *world, deltaTime);
}

void GameLogic::spawnBullet()
{
	// Create bullet object
	bullet = new GameObject();
	bullet->position = player->position;
	bullet->position.y += 1.6f;
	bullet->rotation.y = player->rotation.y * -1.0f;
	bullet->rotation.z = player->rotation.x + 90;
	bullet->rotation.y = bullet->rotation.y + 90;
	bullet->velocity = {
		sin(degreeToRad(player->rotation.y)) *
		cos(degreeToRad(-player->rotation.x)),
		sin(degreeToRad(-player->rotation.x)),
		cos(degreeToRad(player->rotation.y)) *
		cos(degreeToRad(-player->rotation.x)) };
	bullet->velocity *= 50.0f;
	bullet->scale = { 0.01f, 0.01f, 0.01f };
	bullet->addComponent(new ModelComponent("bullet", false));
	bullet->addComponent(new CollisionComponent());
	bullet->addComponent(new BulletComponent(bullet));
}

void GameLogic::handleBullets()
{
	// Add a bullet to the list of objects if it has been spawned
	if (bullet)
	{
		objects.push_back(bullet);
		bullet = nullptr;
	}

	for (auto it = objects.begin(); it != objects.end(); ++it)
		if ((*it)->getComponent<BulletComponent>())
			if ((*it)->getComponent<BulletComponent>()->hasHit)
				objects.erase(it--);
}

void GameLogic::spawnAI()
{
	// Create AI
	auto ai = new GameObject();
	world->setOnRandomEmptyBlock(ai->position);
	ai->scale = { 0.2f, 0.2f, 0.2f };
	ai->addComponent(new ModelComponent("enemy", false));
	ai->addComponent(new CollisionComponent());
	ai->addComponent(new AIComponent(ai, player));
	objects.push_back(ai);
}

void GameLogic::handleAI(const float deltaTime)
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
		if ((*it)->getComponent<AIComponent>())
			if ((*it)->getComponent<AIComponent>()->isDead)
				objects.erase(it--);

	spawnCounter += deltaTime;
	if (spawnCounter > 3)
	{
		spawnCounter = 0;
		spawnAI();
	}
}

float GameLogic::degreeToRad(const float degree)
{
	return static_cast<float>(degree * M_PI / 180.0f);
}

std::vector<GameObject*> GameLogic::getObjects() const
{
	return objects;
}

GameObject *GameLogic::getPlayer() const
{
	return player;
}
