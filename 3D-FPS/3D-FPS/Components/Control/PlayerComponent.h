#pragma once

#include "ControlComponent.h"
#include "../../Math/Vec.h"

class PlayerComponent : public ControlComponent
{
	const float WALK_SPEED = 4.8f;
	const float RUN_SPEED = 6.0f;
	const float ACCELERATION = 1.0f;
	bool previousPositiveY;

public:
	float headHeight = 1.62f;

	PlayerComponent(GameObject &player);

	void update(float elapsedTime) override;
	static Vec3f convertHeading(float rotation, float strafe, float forward, float multiplier);
};
