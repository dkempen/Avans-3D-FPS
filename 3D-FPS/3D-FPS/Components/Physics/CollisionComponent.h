#pragma once

#include "PhysicsComponent.h"
#include "../../Game/World.h"
#include "../../Game/GameLogic.h"

class CollisionComponent : public PhysicsComponent
{
	void collideWithNearbyBoxes(std::vector<GameObject *> gameObjects, World &world, float elapsedTime) const;
	void calculateOffsetX(BoundingBox &box, BoundingBox &other, float &dx) const;
	void calculateOffsetY(BoundingBox &box, BoundingBox &other, float &dy) const;
	void calculateOffsetZ(BoundingBox &box, BoundingBox &other, float &dz) const;
public:
	void update(GameLogic &gameLogic, World &world, float elapsedTime) override;
};
