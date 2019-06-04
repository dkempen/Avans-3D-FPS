#include "TextureComponent.h"
#include <GL/freeglut.h>
#include "../../Data/TextureManager.h"
#include "../../DataManager.h"

TextureComponent::TextureComponent(const Block::BlockType block)
: block(block), size(1)
{
}

TextureComponent::~TextureComponent() = default;

void TextureComponent::draw()
{
	float x1, y1, x2, y2;
	DataManager::getInstance().getBlockCoords(block, x1, y1, x2, y2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, DataManager::getInstance().textureManager.getTextureId());
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);

	const auto s = -size;

	// Bottom
	glTexCoord2f(x1, y1); glVertex3f(s, 0, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, 0, s);

	// Top
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, s, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, s, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);

	// Back
	glTexCoord2f(x1, y1); glVertex3f(0, s, s);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(s, s, s);

	// Front
	glTexCoord2f(x1, y1); glVertex3f(s, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(0, s, 0);

	// Right
	glTexCoord2f(x1, y1); glVertex3f(s, s, s);
	glTexCoord2f(x1, y2); glVertex3f(s, 0, s);
	glTexCoord2f(x2, y2); glVertex3f(s, 0, 0);
	glTexCoord2f(x2, y1); glVertex3f(s, s, 0);

	// Left
	glTexCoord2f(x1, y1); glVertex3f(0, s, 0);
	glTexCoord2f(x1, y2); glVertex3f(0, 0, 0);
	glTexCoord2f(x2, y2); glVertex3f(0, 0, s);
	glTexCoord2f(x2, y1); glVertex3f(0, s, s);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
