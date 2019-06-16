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
	weapon->position.x = 5;
	weapon->position.z = 5;
	weapon->position.y = 1;
	weapon->addComponent(new ModelComponent("weapon"));
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
	for (auto &o : objects)
		o->update(*this, *world, deltaTime);
}

GameObject *GameLogic::getPlayer() const
{
	return player;
}
