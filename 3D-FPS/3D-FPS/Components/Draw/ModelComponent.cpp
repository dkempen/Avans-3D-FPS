#include "ModelComponent.h"
#include <GL/freeglut.h>
#include <cstdint>
#include "../../Math/Vec.h"
#include "../../Math/Graphics.h"
#include "../../Data/DataManager.h"

extern Vec2f cursorOffset;

ModelComponent::ModelComponent(const std::string& modelName, const bool weaponOverlay)
	: mesh(DataManager::getInstance().getMesh(modelName)),
	texture(DataManager::getInstance().getTexture(modelName)),
	weaponOverlay(weaponOverlay)
{
}

ModelComponent::~ModelComponent() = default;

void ModelComponent::draw()
{
	if (weaponOverlay)
	{
		glLoadIdentity();

		glTranslatef(gameObject->position.x, gameObject->position.y, gameObject->position.z);
		// TODO: Smoothing
		glTranslatef(cursorOffset.x / 1000.0f, cursorOffset.y / 1000.0f, 0);
		glTranslatef(offset.x, offset.y, offset.z);
		glScalef(gameObject->scale.x, gameObject->scale.y, gameObject->scale.z);
		glRotatef(gameObject->rotation.x, 1, 0, 0);
		glRotatef(gameObject->rotation.y, 0, 1, 0);
		glRotatef(gameObject->rotation.z, 0, 0, 1);
	}

	glScalef(-1, -1, -1);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor3f(1.0f, 1.0f, 1.0f);

	const uint8_t containerSize = sizeof(Vec3f) / sizeof(float);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Graphics::Vertex), (float*)mesh.vertices.data() + containerSize * 2);
	glNormalPointer(GL_FLOAT, sizeof(Graphics::Vertex), (float*)mesh.vertices.data() + containerSize);
	glVertexPointer(3, GL_FLOAT, sizeof(Graphics::Vertex), (float*)mesh.vertices.data());

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(mesh.vertices.size()));
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
