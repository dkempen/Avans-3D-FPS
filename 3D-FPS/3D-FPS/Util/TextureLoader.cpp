#include "TextureLoader.h"
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../Extern/stb_image.h"

uint16_t TextureLoader::addTexture(const std::string &imagePath, const size_t &amountOfTextures)
{
	auto textureId = static_cast<GLuint>(amountOfTextures);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int width, height, nrChannels;
	if (imagePath != "Resources/Atlas/atlas.png")
		stbi_set_flip_vertically_on_load(true);
	const auto data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels, 4);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		width,
		height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data);

	stbi_image_free(data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return textureId;
}
