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
	player->addComponent(new PlayerComponent(*player));
	player->addComponent(new CollisionComponent());
	objects.push_back(player);

	// Create cube in the center of the world
	auto o = new GameObject();
	o->addComponent(new CubeComponent(1));
	o->position = Vec3f(0, 0, 0);
	objects.push_back(o);

	// Create a plane
	o = new GameObject();
	o->addComponent(new CubeComponent(1));
	o->position.y = -0.5;
	o->scale = Vec3f(10, 1, 10);
	objects.push_back(o);

	// Create small cube in the y axis of the world
	o = new GameObject();
	o->addComponent(new CubeComponent(0.5));
	o->position = Vec3f(0, 2, 0);
	objects.push_back(o);

	// Create super small cube
	o = new GameObject();
	o->addComponent(new CubeComponent(0.2f));
	o->position = Vec3f(2, 2, 2);
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
