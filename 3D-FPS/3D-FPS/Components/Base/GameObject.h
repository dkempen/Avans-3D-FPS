#pragma once

#include <list>
#include "../../Math/Vec.h"
#include "Component.h"
#include "../../Game/World.h"
#include "../Draw/DrawComponent.h"
#include "../Control/ControlComponent.h"
#include "../Physics/PhysicsComponent.h"

class PhysicsComponent;
class World;

class GameObject
{
	DrawComponent *drawComponent;
	ControlComponent *controlComponent;
	PhysicsComponent *physicsComponent;

	std::list<Component *> components;
public:
	GameObject();
	~GameObject();

	Vec3f position;
	Vec3f rotation;
	Vec3f scale = Vec3f(1, 1, 1);
	Vec3f velocity;

	void addComponent(Component *component);
	std::list<Component *> getComponents();
	void update(World &world, float elapsedTime);
	void draw();

	template<class T>
	T* getComponent()
	{
		for (auto c : components)
		{
			T* t = dynamic_cast<T*>(c);
			if (t)
				return t;
		}
		return nullptr;
	}

	template<class T>
	void removeComponent()
	{
		components.remove_if([](Component* c)
		{
			T* t = dynamic_cast<T*>(c);
			return t != nullptr;
		});
	}
};
