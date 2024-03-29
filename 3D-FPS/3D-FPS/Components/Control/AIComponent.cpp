#include "AIComponent.h"
#include "../Base/GameObject.h"
#include "../Control/PlayerComponent.h"
#include <corecrt_math_defines.h>

AIComponent::AIComponent(GameObject *gameObject, GameObject *player) : player(player), isDead(false), isFalling(false)
{
	const auto width = 0.3f;
	const auto height = 1.8f;
	gameObject->boundingBox.min = { -width, 0, -width };
	gameObject->boundingBox.max = { width, height, width };
}

void AIComponent::update(const float elapsedTime)
{
	// Check if it's dead
	if (isDead)
		return;

	// Else rotate it
	gameObject->rotation.y += elapsedTime * 1000.f;
	if (gameObject->rotation.y <= 360)
		gameObject->rotation.y -= 360;

	// And check if it's in the falling state
	if (isFalling)
	{
		gameObject->rotation.x -= elapsedTime * 100.f;
		if (gameObject->rotation.x <= -90)
			isDead = true;
		return;
	}

	// Else, follow the player
	const auto yRotation = atan2(-player->position.z + gameObject->position.z,
		player->position.x - gameObject->position.x) * 180.0f / M_PI + 90.0f;
	gameObject->velocity = PlayerComponent::convertHeading(static_cast<float>(yRotation), 0, 1, SPEED);
}

void AIComponent::bulletHit()
{
	isFalling = true;
	gameObject->velocity *= 0;
}
