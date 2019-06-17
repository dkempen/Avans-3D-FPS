#include "WeaponComponent.h"
#include "../../Game/GameLogic.h"
#include "../Draw/ModelComponent.h"

extern bool leftMouse;

WeaponComponent::WeaponComponent() : cooldown()
{
}

WeaponComponent::~WeaponComponent() = default;

void WeaponComponent::update(GameLogic& gameLogic, const float elapsedTime)
{
	const auto offset = &gameObject->getComponent<ModelComponent>()->offset;
	cooldown -= elapsedTime;
	if (leftMouse)
	{
		if (cooldown <= 0)
		{
			// Reset cooldown
			cooldown = 0.1f;

			// Set weapon model offset
			offset->z = 0.5f;
			
			// Spawn bullet
			gameLogic.spawnBullet();
		}
	}

	offset->z -= elapsedTime * 10.0f * offset->z;
	if (offset->z < 0)
		offset->z = 0;
}
