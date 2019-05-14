#include "PlayerComponent.h"
#include "GameObject.h"
#include <corecrt_math_defines.h>

extern bool keys[256];

void moveCamera(float angle, float fac);

PlayerComponent::PlayerComponent() = default;

PlayerComponent::~PlayerComponent() = default;

void PlayerComponent::update(float elapsedTime)
{
	if (keys[int('a')]) movePlayer(0, elapsedTime * speed);
	if (keys[int('d')]) movePlayer(180, elapsedTime * speed);
	if (keys[int('w')]) movePlayer(90, elapsedTime * speed);
	if (keys[int('s')]) movePlayer(270, elapsedTime * speed);
	if (keys[int('e')]) gameObject->position.z += elapsedTime * speed;
	if (keys[int('q')]) gameObject->position.z -= elapsedTime * speed;
}

void PlayerComponent::movePlayer(float angle, float fac)
{
	gameObject->position.x -= float(cos((gameObject->rotation.y + angle) / 180 * M_PI)) * fac;
	gameObject->position.y -= float(sin((gameObject->rotation.y + angle) / 180 * M_PI)) * fac;
}
