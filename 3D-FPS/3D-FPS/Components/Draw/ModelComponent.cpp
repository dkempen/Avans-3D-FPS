#include "ModelComponent.h"
#include <GL/freeglut.h>
#include <cstdint>
#include "../../Math/Vec.h"
#include "../../Math/Graphics.h"
#include "../../Data/DataManager.h"

ModelComponent::ModelComponent(const std::string &mesh, const std::string &texture)
{
	this->mesh = mesh;
	this->texture = texture;
}

ModelComponent::~ModelComponent() = default;

void ModelComponent::draw()
{
	auto meshReal = DataManager::getInstance().getMesh(mesh);
	const auto textureReal = DataManager::getInstance().getTexture(texture);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor3f(1.0f, 1.0f, 1.0f);

	//The amount of elements in the vec3d struct.
	const uint8_t containerSize = sizeof(Vec3f) / sizeof(float);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Graphics::Vertex), (float*)meshReal.vertices.data() + containerSize * 2);
	glNormalPointer(GL_FLOAT, sizeof(Graphics::Vertex), (float*)meshReal.vertices.data() + containerSize);
	glVertexPointer(3, GL_FLOAT, sizeof(Graphics::Vertex), (float*)meshReal.vertices.data());

	glBindTexture(GL_TEXTURE_2D, textureReal);
	glEnable(GL_TEXTURE_2D);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(meshReal.vertices.size()));
	glDisable(GL_TEXTURE_2D);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}
