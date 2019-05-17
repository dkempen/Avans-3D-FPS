#include "PlayerComponent.h"
#include <corecrt_math_defines.h>
#include "../../Math/Vec.h"
#include "../Base/GameObject.h"

extern bool keys[256];
extern Vec2f cursorOffset;

PlayerComponent::PlayerComponent() = default;

PlayerComponent::~PlayerComponent() = default;

void PlayerComponent::update(float elapsedTime)
{
	hasMoved = false;
	if (keys[int('a')]) movePlayer(0, elapsedTime);
	if (keys[int('d')]) movePlayer(180, elapsedTime);
	if (keys[int('w')]) movePlayer(90, elapsedTime);
	if (keys[int('s')]) movePlayer(270, elapsedTime);
	if (keys[int(' ')] && gameObject->position.y <= 0) gameObject->velocity.y = 1;
	// if (keys[int('q')]) gameObject->position.y -= elapsedTime * MAX_SPEED;

	if (!hasMoved)
	{
		gameObject->velocity.x = 0;
		gameObject->velocity.z = 0;
	}

	if (cursorOffset.x == 0 && cursorOffset.y == 0)
		return;

	gameObject->rotation.x += cursorOffset.y / 10.0f;
	gameObject->rotation.y += cursorOffset.x / 10.0f;
	cursorOffset = { 0, 0 };
	if (gameObject->rotation.x < -90)
		gameObject->rotation.x = -90;
	if (gameObject->rotation.x > 90)
		gameObject->rotation.x = 90;
	if (gameObject->rotation.y > 360)
		gameObject->rotation.y -= 360;
	if (gameObject->rotation.y <= 0)
		gameObject->rotation.y += 360;
}

void PlayerComponent::movePlayer(float angle, float elapsedTime)
{
	hasMoved = true;

	float maxX = float(cos((gameObject->rotation.y + angle) / 180 * M_PI)) * MAX_SPEED;
	gameObject->velocity.x = -maxX;
	// if (maxX < 0)
	// 	gameObject->velocity.x -= ACCELERATION * elapsedTime;
	// else
	// 	gameObject->velocity.x += ACCELERATION * elapsedTime;

	float maxZ = float(sin((gameObject->rotation.y + angle) / 180 * M_PI)) * MAX_SPEED;
	gameObject->velocity.z = maxZ;
	// if (maxY < 0)
	// 	gameObject->velocity.z -= ACCELERATION * elapsedTime;
	// else
	// 	gameObject->velocity.z += ACCELERATION * elapsedTime;

	// gameObject->velocity.z += float(sin((gameObject->rotation.y + angle) / 180 * M_PI)) * elapsedTime;
}
