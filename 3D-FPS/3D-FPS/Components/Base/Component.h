#pragma once

class GameObject;

class Component
{
protected:
	GameObject* gameObject{};
public:
	Component();
	virtual ~Component();

	void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};
