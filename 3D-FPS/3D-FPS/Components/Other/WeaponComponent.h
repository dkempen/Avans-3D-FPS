#pragma once

#include "OtherComponent.h"

class WeaponComponent : public OtherComponent
{
	float cooldown;
public:
	WeaponComponent();
	~WeaponComponent();

	void update(GameLogic &gameLogic, float elapsedTime) override;
};
