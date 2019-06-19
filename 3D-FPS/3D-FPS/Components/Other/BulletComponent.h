#pragma once

#include "OtherComponent.h"

class BulletComponent : public OtherComponent
{
public:
	bool hasHit;

	BulletComponent(GameObject *gameObject);
	~BulletComponent();

	void update(GameLogic &gameLogic, float elapsedTime) override;
};
