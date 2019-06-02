#pragma once
#include <GL/freeglut.h>
#include <string>

class TextureManager
{
	// union Block
	// {
	// 	struct TextureCoords
	// 	{
	// 		int x1, y1, x2, y2;
	// 	};
	// 	int t[4]{};
	//
	// 	struct
	// 	{
	// 		float x, y, z;
	// 	};
	// 	float v[3]{};
	// } block;

	GLuint textureId;
	std::string atlas;
public:
	TextureManager(GLuint textureId, std::string atlas);
	~TextureManager();

	void loadTexture();
};
