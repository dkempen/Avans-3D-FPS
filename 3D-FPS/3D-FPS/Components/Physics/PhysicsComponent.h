#pragma once

#include "../Base/Component.h"
#include "../../Game/World.h"

class World;
class GameLogic;

class PhysicsComponent : public Component
{
public:
	virtual void update(GameLogic &gameLogic, World &world, float elapsedTime) = 0;
};
