#pragma once

#include "Component.h"

class PlayerComponent : public Component
{
	float speed = 3;

	void movePlayer(float angle, float fac);
public:
	float headHeight = 1.75;

	PlayerComponent();
	~PlayerComponent();

	void update(float elapsedTime) override;
};
