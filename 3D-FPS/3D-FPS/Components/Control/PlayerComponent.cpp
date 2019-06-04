#include "PlayerComponent.h"
#include <corecrt_math_defines.h>
#include "../../Math/Vec.h"
#include "../Base/GameObject.h"
#include <algorithm>

extern bool keys[256];
extern Vec2f cursorOffset;

PlayerComponent::PlayerComponent(GameObject &player)
{
	const auto width = 0.3f;
	const auto height = 1.8f;
	player.boundingBox.min = { -width, 0, -width };
	player.boundingBox.max = { width, height, width };
	player.rotation.z = 180;
}

void PlayerComponent::update(float elapsedTime)
{
	float strafe = 0, forward = 0;

	if (keys[int('w')])
		forward = 1;
	if (keys[int('s')])
		forward = -1;
	if (keys[int('w')] && keys[int('s')])
		forward = 0;

	if (keys[int('a')])
		strafe = 1;
	if (keys[int('d')])
		strafe = -1;
	if (keys[int('a')] && keys[int('d')])
		strafe = 0;

	// TODO: Cleanup
	const auto vector = convertHeading(strafe, forward, WALK_SPEED);
	auto slipperiness = 0.6f;
	slipperiness = slipperiness * 0.91f;
	const auto multiplier = 0.1f * (0.1627714f / std::pow(slipperiness, 3));
	const auto vel = vector * multiplier;
	gameObject->velocity.x += vel.x;
	if (strafe != 0 || forward != 0 && abs(gameObject->velocity.x) > vector.x)
		gameObject->velocity.x = vector.x;
	gameObject->velocity.z += vel.z;
	if (strafe != 0 || forward != 0 && abs(gameObject->velocity.z) > vector.z)
		gameObject->velocity.z = vector.z;
	gameObject->velocity.x *= 1 - 20.0f * elapsedTime;
	gameObject->velocity.z *= 1 - 20.0f * elapsedTime;
	gameObject->velocity.maxXZ(WALK_SPEED);

	if (!previousPositiveY && keys[int(' ')] && gameObject->velocity.y == 0)
	{
		previousPositiveY = true;
		gameObject->velocity.y = 8;
	}
	if (previousPositiveY && gameObject->velocity.y < 0.0f)
		previousPositiveY = false;

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

Vec3f PlayerComponent::convertHeading(float strafe, float forward, const float multiplier) const
{
	auto speed = float(sqrt(strafe * strafe + forward * forward));
	if (speed < 0.01)
		return { 0, 0, 0 };

	speed = multiplier / float(std::max(speed, 1.0f));

	strafe *= speed;
	forward *= speed;

	const auto yawXComponent = float(cos(gameObject->rotation.y * (M_PI / 180.0f)));
	const auto yawZComponent = float(sin(gameObject->rotation.y * (M_PI / 180.0f)));

	const auto xComponent = forward * yawZComponent - strafe * yawXComponent;
	const auto zComponent = forward * yawXComponent + strafe * yawZComponent;

	return { xComponent, 0, zComponent };
}
