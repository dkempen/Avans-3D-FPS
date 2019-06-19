#pragma once

#include "ControlComponent.h"

class AIComponent : public ControlComponent
{
	const float SPEED = 3.0f;
	GameObject *player;
public:
	AIComponent(GameObject *gameObject, GameObject *player);

	float headHeight = 1.62f;
	bool isDead;
	bool isFalling;

	void update(float elapsedTime) override;
	void bulletHit();
};
