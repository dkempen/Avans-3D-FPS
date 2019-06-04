#pragma once

#include "DrawComponent.h"

class TextureComponent : public DrawComponent
{
public:
	enum class BlockType { FLOOR, CRATE, WALL };

	TextureComponent(BlockType block);
	~TextureComponent();

	void draw() override;
private:
	BlockType block;
	float size;
};
