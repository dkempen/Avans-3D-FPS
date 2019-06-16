#pragma once

#include "../Base/Component.h"

class GameLogic;

class OtherComponent : public Component
{
public:
	OtherComponent();
	~OtherComponent();

	virtual void update(GameLogic &gameLogic, float elapsedTime) = 0;
};
