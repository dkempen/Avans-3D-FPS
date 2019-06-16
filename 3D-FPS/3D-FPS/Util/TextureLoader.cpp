#include "TextureLoader.h"
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../Extern/stb_image.h"

uint16_t TextureLoader::addTexture(const std::string &image_path, const size_t &amount_of_textures)
{
	auto textureId = static_cast<GLuint>(amount_of_textures);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	int width, height, nrChannels;
	// stbi_set_flip_vertically_on_load(true);
	const auto data = stbi_load(image_path.c_str(), &width, &height, &nrChannels, 4);

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
