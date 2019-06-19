#include "GameObject.h"
#include <GL/freeglut.h>

GameObject::GameObject()
	: scale(1, 1, 1)
{
}

void GameObject::addComponent(Component *component)
{
	// Adds a new component to the gameObject
	component->setGameObject(this);
	components.push_back(component);

	// Checks whether it is a type of Component, and replaces it
	if (dynamic_cast<DrawComponent *>(component))
		drawComponent = dynamic_cast<DrawComponent *>(component);
	if (dynamic_cast<ControlComponent *>(component))
		controlComponent = dynamic_cast<ControlComponent *>(component);
	if (dynamic_cast<PhysicsComponent *>(component))
		physicsComponent = dynamic_cast<PhysicsComponent *>(component);
	if (dynamic_cast<OtherComponent *>(component))
		otherComponent = dynamic_cast<OtherComponent *>(component);
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

	if (drawComponent)
		drawComponent->draw();

	glPopMatrix();
}

void GameObject::update(GameLogic &gameLogic, World &world, const float elapsedTime) const
{
	if (controlComponent) controlComponent->update(elapsedTime);
	if (physicsComponent) physicsComponent->update(gameLogic, world, elapsedTime);
	if (otherComponent)   otherComponent->update(gameLogic, elapsedTime);
}
