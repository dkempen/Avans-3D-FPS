#include "TextureComponent.h"
#include <GL/freeglut.h>

TextureComponent::TextureComponent(float size)
{
	this->size = size;
}

TextureComponent::~TextureComponent() = default;

void TextureComponent::draw()
{
	// if (blockId == AIR)
	// 	return;
	// block block = blocks[blockId];
	//
	// glEnable(GL_TEXTURE_2D);
	// glBindTexture(GL_TEXTURE_2D, minecraftTexture);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	const auto s = -size;
	float x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	// Bottom
	// getTileCoords(block.u, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(s, 0, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, 0, s);

	// Top
	// getTileCoords(block.t, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, s, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, s, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);

	// Back
	// getTileCoords(block.b, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(0, s, s);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(s, s, s);

	// Front
	// getTileCoords(block.f, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(s, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, 0);

	// Right
	// getTileCoords(block.r, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(s, s, 0);

	// Left
	// getTileCoords(block.l, x1, y1, x2, y2);
	glTexCoord2f(x1, y1); glVertex3f(0, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
