#include "GameLogic.h"
#include "../Components/Base/GameObject.h"
#include "../Components/Control/PlayerComponent.h"
#include "../Components/Physics/CollisionComponent.h"
#include "../Components/Draw/ModelComponent.h"
#include "../Components/Other/WeaponComponent.h"

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
	// Add a bullet to the list of objects if it has been spawned
	if (bullet)
	{
		objects.push_back(bullet);
		bullet = nullptr;
	}

	for (auto &o : objects)
		o->update(*this, *world, deltaTime);
}

GameObject *GameLogic::getPlayer() const
{
	return player;
}

void GameLogic::spawnBullet()
{
	// Create bullet object
	bullet = new GameObject();
	bullet->position = player->position;
	bullet->position.y += 1.6f;
	// bullet->position.z += 0.5f;
	bullet->rotation = player->rotation;
	bullet->scale = { 0.1f, 0.1f, 0.1f };
	bullet->addComponent(new ModelComponent("weapon", false));
	// bullet->addComponent(new BulletComponent());
}
