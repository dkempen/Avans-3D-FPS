#pragma once

#include "ControlComponent.h"
#include "../../Math/Vec.h"

class PlayerComponent : public ControlComponent
{
	const float WALK_SPEED = 4.3f;
	const float ACCELERATION = 1.0f;

	Vec3f convertHeading(float strafe, float forward, float multiplier) const;
public:
	PlayerComponent(GameObject &player);

	float headHeight = 1.62f;

	void update(float elapsedTime) override;
};
