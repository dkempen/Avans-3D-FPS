#pragma once

#include "../Base/Component.h"

class ControlComponent : public Component
{
public:
	ControlComponent();
	~ControlComponent();

	virtual void update(float elapsedTime) {};
};
