#include "WeaponComponent.h"
#include "../Base/GameObject.h"
#include "../../Game/GameLogic.h"

WeaponComponent::WeaponComponent() = default;

WeaponComponent::~WeaponComponent() = default;

void WeaponComponent::update(GameLogic& gameLogic, float elapsedTime)
{
	auto player = gameLogic.getPlayer();
	gameObject->position = player->position;
	gameObject->position.y += 1;

	gameObject->rotation.z = player->rotation.x;
	gameObject->rotation.y = -player->rotation.y;
	gameObject->rotation.y += 90;
}
