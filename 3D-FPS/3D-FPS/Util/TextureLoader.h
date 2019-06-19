#pragma once

#include <string>

class TextureLoader
{
public:
	/*
		Reads a texture from an image, and adds it to OpenGL

		@param image_path - The relative path of the image
		@param amount_of_textures - The amount of textures that already exist

		Returns the id of the texture
	*/
	static uint16_t addTexture(const std::string &imagePath, const size_t &amountOfTextures);
};
