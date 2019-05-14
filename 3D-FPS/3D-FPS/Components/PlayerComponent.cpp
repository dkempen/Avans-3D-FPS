#include "PlayerComponent.h"
#include "GameObject.h"
#include <corecrt_math_defines.h>

extern bool keys[256];
extern int cursorOffsetX, cursorOffsetY;

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

	if (cursorOffsetX == 0 && cursorOffsetY == 0)
		return;

	gameObject->rotation.x += cursorOffsetY / 10.0f;
	gameObject->rotation.y += cursorOffsetX / 10.0f;
	cursorOffsetX = 0;
	cursorOffsetY = 0;
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
