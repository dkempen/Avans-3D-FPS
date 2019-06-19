#include "GameObject.h"
#include <GL/freeglut.h>

GameObject::GameObject()
	: scale(1, 1, 1)
{
}

void GameObject::addComponent(Component *component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (dynamic_cast<DrawComponent *>(component))
		drawComponents.emplace_back(dynamic_cast<DrawComponent *>(component));
	if (dynamic_cast<ControlComponent *>(component))
		controlComponents.emplace_back(dynamic_cast<ControlComponent *>(component));
	if (dynamic_cast<PhysicsComponent *>(component))
		physicsComponents.emplace_back(dynamic_cast<PhysicsComponent *>(component));
	if (dynamic_cast<OtherComponent *>(component))
		otherComponents.emplace_back(dynamic_cast<OtherComponent *>(component));
}

std::list<Component *> GameObject::getComponents() const
{
	return components;
}

void GameObject::draw() const
{
	glPushMatrix();

	glTranslatef(-position.x, -position.y, -position.z);
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(-rotation.x, 1, 0, 0);
	glRotatef(-rotation.y, 0, 1, 0);
	glRotatef(-rotation.z, 0, 0, 1);

	for (auto component : drawComponents)
		component->draw();

	glPopMatrix();
}

void GameObject::update(GameLogic &gameLogic, World &world, const float elapsedTime) const
{
	for (auto component : controlComponents)
		component->update(elapsedTime);
	for (auto component : physicsComponents)
		component->update(gameLogic, world, elapsedTime);
	for (auto component : otherComponents)
		component->update(gameLogic, elapsedTime);
}
