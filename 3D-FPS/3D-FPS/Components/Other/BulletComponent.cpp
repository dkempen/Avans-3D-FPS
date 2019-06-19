#include "BulletComponent.h"
#include "../Base/GameObject.h"

BulletComponent::BulletComponent(GameObject *gameObject): hasHit(false)
{
	const auto width = 0.1f;
	const auto height = 0.1f;
	gameObject->boundingBox.min = { -width, 0, -width };
	gameObject->boundingBox.max = { width, height, width };
}

BulletComponent::~BulletComponent() = default;

void BulletComponent::update(GameLogic& gameLogic, float elapsedTime)
{
	if (gameObject->velocity.x == 0 || gameObject->velocity.y == 0 || gameObject->velocity.z == 0)
	{
		hasHit = true;
	}
}
