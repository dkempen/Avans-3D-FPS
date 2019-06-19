#include "CollisionComponent.h"
#include "../Other/BulletComponent.h"
#include "../Control/AIComponent.h"

void CollisionComponent::update(GameLogic &gameLogic, World &world, float elapsedTime)
{
	collideWithNearbyBoxes(gameLogic.getObjects(), world, elapsedTime);
}

void CollisionComponent::collideWithNearbyBoxes(std::vector<GameObject *> gameObjects, World &world, float elapsedTime) const
{
	// Get current object bounding box
	auto current = gameObject->boundingBox.getAbsoluteBox(gameObject->position);

	// Check floor
	gameObject->velocity.y -= 25.0f * elapsedTime;
	if (gameObject->position.y < -10.0f)
	{
		gameObject->position = { 5, 0, 5 };
		gameObject->velocity = { 0, 0, 0 };
	}

	// Calculate position offset
	auto dx = gameObject->velocity.x * elapsedTime;
	auto dy = gameObject->velocity.y * elapsedTime;
	auto dz = gameObject->velocity.z * elapsedTime;

	// Get world coords
	const auto x = int(gameObject->position.x + dx);
	const auto z = int(gameObject->position.z + dz);

	// Bounding box of the "other" object
	BoundingBox other;

	// Check Ceiling
	other.min = { 0.0f, 4.0f, 0.0f };
	other.max = { 20.0f, 5.0f, 20.0f };
	calculateOffsetY(current, other, dy);

	// Check world
	for (auto xx = -1; xx <= 1; ++xx)
		for (auto zz = -1; zz <= 1; ++zz)
		{
			const auto blockHeight = world.getBlockHeight(x + xx, z + zz);
			if (blockHeight >= 0.0f)
			{
				other.min = { x + xx + 0.0f, 0.0f, z + zz + 0.0f };
				other.max = { x + xx + 1.0f, blockHeight, z + zz + 1.0f };
				calculateOffsetY(current, other, dy);
				calculateOffsetX(current, other, dx);
				calculateOffsetZ(current, other, dz);
			}
		}

	// Check entities
	for (auto object : gameObjects)
	{
		if (object != gameObject && object->getComponent<CollisionComponent>())
		{
			const auto prevX = gameObject->velocity.x;
			const auto prevY = gameObject->velocity.y;
			const auto prevZ = gameObject->velocity.z;

			other = object->boundingBox.getAbsoluteBox(object->position);
			calculateOffsetY(current, other, dy);
			calculateOffsetX(current, other, dx);
			calculateOffsetZ(current, other, dz);

			// Send hit message to object if bullet has hit an object with an AIComponent
			if (gameObject->getComponent<BulletComponent>())
				if (prevX != 0 && gameObject->velocity.x == 0 ||
					prevY != 0 && gameObject->velocity.y == 0 ||
					prevZ != 0 && gameObject->velocity.z == 0 &&
					object->getComponent<AIComponent>())
					object->getComponent<AIComponent>()->bulletHit();
		}
	}

	// Set new position
	gameObject->position.x += dx;
	gameObject->position.y += dy;
	gameObject->position.z += dz;
}

void CollisionComponent::calculateOffsetX(BoundingBox &box, BoundingBox &other, float &dx) const
{
	// Bail out if not within the same Y/Z plane.
	if (box.max.y <= other.min.y || box.min.y >= other.max.y)
		return;
	if (box.max.z <= other.min.z || box.min.z >= other.max.z)
		return;

	// The entity is moving POSITIVE and is currently "below" other.
	if (dx > 0 && box.max.x <= other.min.x)
	{
		const auto difference = other.min.x - box.max.x;
		if (difference < dx)
		{
			gameObject->velocity.x = 0;
			dx = difference;
		}
	}

	// The entity is moving NEGATIVE and is currently "above" other.
	if (dx < 0 && box.min.x >= other.max.x)
	{
		const auto difference = other.max.x - box.min.x;
		if (difference > dx)
		{
			gameObject->velocity.x = 0;
			dx = difference + 0.0000001f;
		}
	}
}

void CollisionComponent::calculateOffsetY(BoundingBox &box, BoundingBox &other, float &dy) const
{
	// Bail out if not within the same X/Z plane.
	if (box.max.x <= other.min.x || box.min.x >= other.max.x)
		return;
	if (box.max.z <= other.min.z || box.min.z >= other.max.z)
		return;

	// The entity is moving UP and is currently below other.
	if (dy > 0 && box.max.y <= other.min.y)
	{
		const auto difference = other.min.y - box.max.y;
		if (difference < dy)
		{
			gameObject->velocity.y = 0;
			dy = difference;
		}
	}

	// The entity is moving DOWN and is currently above other.
	if (dy < 0 && box.min.y >= other.max.y)
	{
		const auto difference = other.max.y - box.min.y;
		if (difference > dy)
		{
			gameObject->velocity.y = 0;
			dy = difference + 0.0000001f;
		}
	}
}

void CollisionComponent::calculateOffsetZ(BoundingBox &box, BoundingBox &other, float &dz) const
{
	// Bail out if not within the same X/Y plane.
	if (box.max.x <= other.min.x || box.min.x >= other.max.x)
		return;
	if (box.max.y <= other.min.y || box.min.y >= other.max.y)
		return;

	// The entity is moving POSITIVE and is currently "below" other.
	if (dz > 0 && box.max.z <= other.min.z)
	{
		const auto difference = other.min.z - box.max.z;
		if (difference < dz)
		{
			gameObject->velocity.z = 0;
			dz = difference;
		}
	}

	// The entity is moving NEGATIVE and is currently "above" other.
	if (dz < 0 && box.min.z >= other.max.z)
	{
		const auto difference = other.max.z - box.min.z;
		if (difference > dz)
		{
			gameObject->velocity.z = 0;
			dz = difference + 0.0000001f;
		}
	}
}
