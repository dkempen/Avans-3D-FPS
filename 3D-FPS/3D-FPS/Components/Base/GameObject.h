#pragma once

#include <list>
#include "../../Math/Vec.h"
#include "Component.h"
#include "../Draw/DrawComponent.h"
#include "../Control/ControlComponent.h"

class GameObject
{
	DrawComponent *drawComponent = nullptr;
	ControlComponent *controlComponent = nullptr;

	std::list<Component*> components;
public:
	GameObject();
	~GameObject();

	Vec3f position;
	Vec3f rotation;
	Vec3f scale = Vec3f(1, 1, 1);
	Vec3f velocity;

	void addComponent(Component* component);
	std::list<Component*> getComponents();
	void update(float elapsedTime);
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
