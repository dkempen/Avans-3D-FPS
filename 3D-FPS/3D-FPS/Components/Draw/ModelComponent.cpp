#include "ModelComponent.h"
#include <GL/freeglut.h>
#include <cstdint>
#include "../../Math/Vec.h"
#include "../../Math/Graphics.h"
#include "../../Data/DataManager.h"

ModelComponent::ModelComponent(const std::string& modelName)
	: mesh(DataManager::getInstance().getMesh(modelName)), texture(DataManager::getInstance().getTexture(modelName))
{
}

ModelComponent::~ModelComponent() = default;

void ModelComponent::draw()
{
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
