#include "GameLogic.h"
#include "../Components/Control/PlayerComponent.h"
#include "../Components/Draw/CubeComponent.h"
#include "../Components/Physics/CollisionComponent.h"

GameLogic::GameLogic()
{
	initGame();
}

GameLogic::~GameLogic() = default;

void GameLogic::initGame()
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

	// Create a plane
	auto o = new GameObject();
	o->addComponent(new CubeComponent(1));
	o->position.y = -0.5;
	o->position.x = 5;
	o->position.z = 5;
	o->scale = Vec3f(10, 1, 10);
	objects.push_back(o);
}

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
