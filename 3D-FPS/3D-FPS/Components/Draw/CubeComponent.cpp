#include "CubeComponent.h"
#include <GL/freeglut.h>

CubeComponent::CubeComponent(float size)
{
	this->size = size;
}

CubeComponent::~CubeComponent() = default;

void CubeComponent::draw()
{
	const auto s = size / 2;
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-s, -s, -s);
	glVertex3f(-s, -s, s);
	glVertex3f(-s, s, s);
	glVertex3f(-s, s, -s);

	glVertex3f(s, -s, -s);
	glVertex3f(s, -s, s);
	glVertex3f(s, s, s);
	glVertex3f(s, s, -s);

	glColor3f(0, 1, 0);
	glVertex3f(-s, -s, -s);
	glVertex3f(-s, -s, s);
	glVertex3f(s, -s, s);
	glVertex3f(s, -s, -s);

	glVertex3f(-s, s, -s);
	glVertex3f(-s, s, s);
	glVertex3f(s, s, s);
	glVertex3f(s, s, -s);

	glColor3f(0, 0, 1);
	glVertex3f(-s, -s, -s);
	glVertex3f(-s, s, -s);
	glVertex3f(s, s, -s);
	glVertex3f(s, -s, -s);

	glVertex3f(-s, -s, s);
	glVertex3f(-s, s, s);
	glVertex3f(s, s, s);
	glVertex3f(s, -s, s);

	glEnd();
}
