#include "CollisionComponent.h"

CollisionComponent::CollisionComponent() = default;

CollisionComponent::~CollisionComponent() = default;

void CollisionComponent::update(World &world, float elapsedTime)
{
	// TODO: Check collision

	// Set new position
	gameObject->position.x += gameObject->velocity.x * elapsedTime;
	gameObject->position.y += gameObject->velocity.y * elapsedTime;
	gameObject->position.z += gameObject->velocity.z * elapsedTime;
}
