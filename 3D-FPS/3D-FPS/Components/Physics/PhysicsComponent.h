#pragma once

#include "../Base/Component.h"
#include "../../Game/World.h"

class World;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent();
	~PhysicsComponent();

	virtual void update(World &world, float elapsedTime) {}
};
