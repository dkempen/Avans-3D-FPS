#include "CollisionComponent.h"

void CollisionComponent::update(World &world, float elapsedTime)
{
	collideWithNearbyBoxes(world, elapsedTime);
}

void CollisionComponent::collideWithNearbyBoxes(World &world, float elapsedTime) const
{
	BoundingBox absolute = gameObject->boundingBox.getAbsoluteBox(gameObject->position);

	gameObject->velocity.y -= 20.0f * elapsedTime;
	if (gameObject->position.y < -100.0f)
	{
		gameObject->position = { 5, 0, 5 };
		gameObject->velocity = { 0, 0, 0 };
	}

	auto dx = gameObject->velocity.x * elapsedTime;
	auto dy = gameObject->velocity.y * elapsedTime;
	auto dz = gameObject->velocity.z * elapsedTime;
	
	const auto x = int(gameObject->position.x + dx);
	const auto z = int(gameObject->position.z + dz);

	BoundingBox temp;
	
	// Floor Y bounding box
	temp.min = { 0, -1.0f, 0 };
	temp.max = { 10.0f, 0.0f, 10.0f };
	calculateOffsetY(absolute, temp, dy);

	for (auto xx = -1; xx <= 1; ++xx)
		for (auto zz = -1; zz <= 1; ++zz)
		{
			const auto blockHeight = world.getBlockHeight(x + xx, z + zz);
			if (blockHeight > 0.0f)
			{
				temp.min = { x + xx + 0.0f, 0.0f, z + zz + 0.0f };
				temp.max = { x + xx + 1.0f, blockHeight, z + zz + 1.0f };
				calculateOffsetY(absolute, temp, dy);
				calculateOffsetX(absolute, temp, dx);
				calculateOffsetZ(absolute, temp, dz);
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
