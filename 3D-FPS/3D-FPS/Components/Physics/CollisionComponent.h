#pragma once

#include "PhysicsComponent.h"
#include "../../Game/World.h"

class CollisionComponent : public PhysicsComponent
{
public:
	CollisionComponent();
	~CollisionComponent();

	void update(World &world, float elapsedTime) override;
};
