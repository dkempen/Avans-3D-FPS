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
	if (keys[int('a')]) movePlayer(0, elapsedTime * speed);
	if (keys[int('d')]) movePlayer(180, elapsedTime * speed);
	if (keys[int('w')]) movePlayer(90, elapsedTime * speed);
	if (keys[int('s')]) movePlayer(270, elapsedTime * speed);
	if (keys[int('e')]) gameObject->position.y += elapsedTime * speed;
	if (keys[int('q')]) gameObject->position.y -= elapsedTime * speed;

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

void PlayerComponent::movePlayer(float angle, float fac)
{
	gameObject->position.x -= float(cos((gameObject->rotation.y + angle) / 180 * M_PI)) * fac;
	gameObject->position.z += float(sin((gameObject->rotation.y + angle) / 180 * M_PI)) * fac;
}
