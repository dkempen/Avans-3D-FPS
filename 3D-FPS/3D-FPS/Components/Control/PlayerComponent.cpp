#include "PlayerComponent.h"
#include <corecrt_math_defines.h>
#include "../../Math/Vec.h"
#include "../Base/GameObject.h"
#include <algorithm>

extern bool keys[256];
extern bool leftMouse;
extern Vec2f cursorOffset;

PlayerComponent::PlayerComponent(GameObject &player)
	: previousPositiveY(false)
{
	const auto width = 0.3f;
	const auto height = 1.8f;
	player.boundingBox.min = { -width, 0, -width };
	player.boundingBox.max = { width, height, width };
	player.rotation.z = 180;
}

void PlayerComponent::update(const float elapsedTime)
{
	// Check which direction the player is moving
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

	// Create a movement vector
	auto speedMultiplier = WALK_SPEED;
	if (keys[int('f')])
		speedMultiplier = RUN_SPEED;
	const auto vector = convertHeading(gameObject->rotation.y, strafe, forward, speedMultiplier);

	// Add friction and other nice stuff
	auto slipperiness = 0.6f;
	slipperiness = slipperiness * 0.91f;
	const auto multiplier = 100.0f * (0.1627714f / std::pow(slipperiness, 3));
	const auto vel = vector * multiplier * elapsedTime;

	// Limit the velocity to the max value
	gameObject->velocity.x += vel.x;
	if (strafe != 0 || forward != 0 && abs(gameObject->velocity.x) > vector.x)
		gameObject->velocity.x = vector.x;
	gameObject->velocity.z += vel.z;
	if (strafe != 0 || forward != 0 && abs(gameObject->velocity.z) > vector.z)
		gameObject->velocity.z = vector.z;
	gameObject->velocity.x *= 1 - 20.0f * elapsedTime;
	gameObject->velocity.z *= 1 - 20.0f * elapsedTime;
	gameObject->velocity.maxXZ(speedMultiplier);

	// Jump if space is pressed
	if (!previousPositiveY && keys[int(' ')] && gameObject->velocity.y == 0)
	{
		previousPositiveY = true;
		gameObject->velocity.y = 8;
	}
	if (previousPositiveY && gameObject->velocity.y < 0.0f)
		previousPositiveY = false;

	if (cursorOffset.x == 0 && cursorOffset.y == 0)
		return;

	// Rotate the player if a mouse movement is detected
	gameObject->rotation.x += cursorOffset.y / 10.0f;
	gameObject->rotation.y += cursorOffset.x / 10.0f;
	if (gameObject->rotation.x < -90)
		gameObject->rotation.x = -90;
	if (gameObject->rotation.x > 90)
		gameObject->rotation.x = 90;
	if (gameObject->rotation.y > 360)
		gameObject->rotation.y -= 360;
	if (gameObject->rotation.y <= 0)
		gameObject->rotation.y += 360;
}

// Converts the walking direction and the rotation into a movement vector
Vec3f PlayerComponent::convertHeading(const float rotation, float strafe, float forward, const float multiplier)
{
	auto speed = float(sqrt(strafe * strafe + forward * forward));
	if (speed < 0.01)
		return { 0, 0, 0 };

	speed = multiplier / float(std::max(speed, 1.0f));

	strafe *= speed;
	forward *= speed;

	const auto yawXComponent = float(cos(rotation * (M_PI / 180.0f)));
	const auto yawZComponent = float(sin(rotation * (M_PI / 180.0f)));

	const auto xComponent = forward * yawZComponent - strafe * yawXComponent;
	const auto zComponent = forward * yawXComponent + strafe * yawZComponent;

	return { xComponent, 0, zComponent };
}
