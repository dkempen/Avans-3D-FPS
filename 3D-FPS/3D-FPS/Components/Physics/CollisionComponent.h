#pragma once

#include "PhysicsComponent.h"
#include "../../Game/World.h"

class CollisionComponent : public PhysicsComponent
{
	void collideWithNearbyBoxes(World &world, float elapsedTime) const;
	void calculateOffsetX(BoundingBox &box, BoundingBox &other, float &dx) const;
	void calculateOffsetY(BoundingBox &box, BoundingBox &other, float &dy) const;
	void calculateOffsetZ(BoundingBox &box, BoundingBox &other, float &dz) const;
public:
	void update(World &world, float elapsedTime) override;
};
