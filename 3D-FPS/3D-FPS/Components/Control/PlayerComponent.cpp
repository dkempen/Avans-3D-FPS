#include "PlayerComponent.h"
#include <corecrt_math_defines.h>
#include "../../Math/Vec.h"
#include "../Base/GameObject.h"
#include <algorithm>
#include <valarray>

extern bool keys[256];
extern Vec2f cursorOffset;

PlayerComponent::PlayerComponent() = default;

PlayerComponent::~PlayerComponent() = default;

void PlayerComponent::update(float elapsedTime)
{
	/*hasMoved = false;
	if (keys[int('a')]) movePlayer(0, elapsedTime);
	if (keys[int('d')]) movePlayer(180, elapsedTime);
	if (keys[int('w')]) movePlayer(90, elapsedTime);
	if (keys[int('s')]) movePlayer(270, elapsedTime);
	if (keys[int(' ')] && gameObject->position.y <= 0) gameObject->velocity.y = 1;
	// if (keys[int('q')]) gameObject->position.y -= elapsedTime * WALK_SPEED;

	if (!hasMoved)
	{
		gameObject->velocity.x = 0;
		gameObject->velocity.z = 0;
	}*/

	int strafe = 0, forward = 0;

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

	Vec3f vector = convertHeading(strafe, forward, WALK_SPEED);
	float slipperiness = 0.6;
	slipperiness = slipperiness * 0.91;
	float multiplier = 0.1 * (0.1627714 / std::pow(slipperiness, 3));
	Vec3f vel = vector * multiplier;// *ACCELERATION * 1.0f;
	gameObject->velocity += vel;
	gameObject->velocity *= 0.99;
	gameObject->velocity.max(WALK_SPEED);

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

Vec3f PlayerComponent::convertHeading(int strafe, int forward, const float multiplier) const
{
	float speed = sqrt(strafe * strafe + forward * forward);
	if (speed < 0.01)
		return { 0, 0, 0 };

	speed = multiplier / float(std::max(speed, 1.0f));

	strafe *= speed;
	forward *= speed;

	const float yawXComponent = cos(gameObject->rotation.y * (M_PI / 180.0f));
	const float yawZComponent = sin(gameObject->rotation.y * (M_PI / 180.0f));

	const auto xComponent = forward * yawZComponent - strafe * yawXComponent;
	const auto zComponent = forward * yawXComponent + strafe * yawZComponent;

	return { xComponent, 0, zComponent };
}
