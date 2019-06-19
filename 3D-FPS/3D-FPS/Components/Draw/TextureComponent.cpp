#include "TextureComponent.h"
#include <GL/freeglut.h>
#include <utility>
#include "../../Data/TextureManager.h"
#include "../../Data/DataManager.h"

TextureComponent::TextureComponent(const Block::BlockType block, std::string texture)
	: block(block), size(1), texture(DataManager::getInstance().getTexture(texture))
{
}

TextureComponent::~TextureComponent() = default;

void TextureComponent::draw()
{
	float x1, y1, x2, y2;
	DataManager::getInstance().getBlockCoords(block, x1, y1, x2, y2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	const auto s = -size;

	// Bottom
	glNormal3f(0, 1, 0);
	glTexCoord2f(x1, y1); glVertex3f(s, 0, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, 0, s);

	// Top
	glNormal3f(0, -1, 0);
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, s, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, s, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);

	// Back
	glNormal3f(0, 0, -1);
	glTexCoord2f(x1, y1); glVertex3f(0, s, s);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(s, s, s);

	// Front
	glNormal3f(0, 0, 1);
	glTexCoord2f(x1, y1); glVertex3f(s, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, 0);

	// Right
	glNormal3f(-1, 0, 0);
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(s, s, 0);

	// Left
	glNormal3f(1, 0, 0);
	glTexCoord2f(x1, y1); glVertex3f(0, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
