#include "GameLogic.h"
#include "../Components/Control/PlayerComponent.h"
#include "../Components/Physics/CollisionComponent.h"
#include "../Components/Draw/TextureComponent.h"
#include "../Components/Draw/ModelComponent.h"

GameLogic::GameLogic()
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

	// Create model test object
	auto model = new GameObject();
	model->position.x = 5;
	model->position.z = 5;
	model->position.y = 2;
	model->addComponent(new ModelComponent("packet", "packet"));
	objects.push_back(model);
}

GameLogic::~GameLogic() = default;


void GameLogic::draw()
{
	for (auto &o : objects)
		o->draw();
}

void GameLogic::update(float deltaTime)
{
	for (auto &o : objects)
		o->update(*world, deltaTime);
}

GameObject *GameLogic::getPlayer() const
{
	return player;
}
