#pragma once

#include "ControlComponent.h"

class PlayerComponent : public ControlComponent
{
	const float MAX_SPEED = 3;
	const float ACCELERATION = 1;
	bool hasMoved;

	void movePlayer(float angle, float elapsedTime);
public:
	float headHeight = 1.75;

	PlayerComponent();
	~PlayerComponent();

	void update(float elapsedTime) override;
};
