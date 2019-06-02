#pragma once

#include "DrawComponent.h"

class TextureComponent : public DrawComponent
{
	float size;
public:
	TextureComponent(float size);
	~TextureComponent();

	void draw() override;
};
