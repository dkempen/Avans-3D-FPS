#include "WeaponComponent.h"
#include "../../Game/GameLogic.h"
#include "../Draw/ModelComponent.h"

extern bool leftMouse;
extern Vec2f cursorOffset;

WeaponComponent::WeaponComponent() : cooldown()
{
}

WeaponComponent::~WeaponComponent() = default;

void WeaponComponent::update(GameLogic& gameLogic, const float elapsedTime)
{
	const auto offset = &gameObject->getComponent<ModelComponent>()->positionOffset;
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

	const auto distance = 0.02f;
	const auto speed = 10.0f;

	offset->z -= elapsedTime * speed * offset->z;
	if (offset->z < 0)
		offset->z = 0;

	const Vec2f target = {-cursorOffset.x * distance, cursorOffset.y * distance };

	const auto differenceX = target.x - offset->x;
	offset->x += elapsedTime * speed * differenceX;
	if (differenceX > 0 && offset->x > target.x || differenceX < 0 && offset->x < target.x)
		offset->x = target.x;

	const auto differenceY = target.y - offset->y;
	offset->y += elapsedTime * speed * differenceY;
	if (differenceY > 0 && offset->y > target.y || differenceY < 0 && offset->y < target.y)
		offset->y = target.y;
}
