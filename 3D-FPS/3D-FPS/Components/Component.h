#pragma once

class GameObject;

class Component
{
protected:
	GameObject* gameObject{};
public:
	Component();
	virtual ~Component();

	virtual void update(float elapsedTime) {}

	void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};
