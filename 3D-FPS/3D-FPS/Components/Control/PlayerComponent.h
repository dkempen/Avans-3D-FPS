#pragma once

#include "ControlComponent.h"
#include "../../Math/Vec.h"

class PlayerComponent : public ControlComponent
{
	const float WALK_SPEED = 4.3;
	const float ACCELERATION = 1;

	Vec3f convertHeading(int strafe, int forward, float multiplier) const;
public:
	float headHeight = 1.62;

	PlayerComponent();
	~PlayerComponent();

	void update(float elapsedTime) override;
};
