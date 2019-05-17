#include "GameObject.h"
#include <GL/freeglut.h>

GameObject::GameObject()
{
	scale = { 1, 1, 1 };
};

// GameObject::~GameObject() = default;

void GameObject::addComponent(Component * component)
{
	component->setGameObject(this);
	components.push_back(component);

	if (!drawComponent)
		drawComponent = dynamic_cast<DrawComponent *>(component);
	if (!controlComponent)
		controlComponent = dynamic_cast<ControlComponent *>(component);
	if (!physicsComponent)
		physicsComponent = dynamic_cast<PhysicsComponent *>(component);
}

std::list<Component*> GameObject::getComponents()
{
	return components;
}


void GameObject::draw()
{
	if (!drawComponent)
		return;

	glPushMatrix();
	glScalef(scale.x, scale.y, scale.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);
	glTranslatef(-position.x, -position.y, -position.z);
	drawComponent->draw();
	glPopMatrix();
}

void GameObject::update(World &world, float elapsedTime)
{
	if (controlComponent) controlComponent->update(elapsedTime);
	if (physicsComponent) physicsComponent->update(world, elapsedTime);
	// for (auto &c : components)
	// 	c->update(elapsedTime);
}
