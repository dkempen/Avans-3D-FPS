#pragma once

#include "../../Math/Vec.h"
#include "../../Math/BoundingBox.h"
#include "Component.h"
#include "../Draw/DrawComponent.h"
#include "../Control/ControlComponent.h"
#include "../Physics/PhysicsComponent.h"
#include "../Other/OtherComponent.h"
#include <list>

class PhysicsComponent;
class World;

class GameObject
{
	std::vector<DrawComponent *>drawComponents;
	std::vector<ControlComponent *>controlComponents;
	std::vector<PhysicsComponent *>physicsComponents;
	std::vector<OtherComponent *>otherComponents;

	std::list<Component *> components;
public:
	Vec3f position;
	Vec3f rotation;
	Vec3f scale;

	Vec3f velocity;

	BoundingBox boundingBox;

	GameObject();
	~GameObject() = default;

	void addComponent(Component *component);
	std::list<Component *> getComponents() const;
	void update(GameLogic &gameLogic, World &world, float elapsedTime) const;
	void draw() const;

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
