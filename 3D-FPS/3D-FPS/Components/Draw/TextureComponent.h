#pragma once

#include "DrawComponent.h"
#include "../../Game/Block.h"
#include <string>

class TextureComponent : public DrawComponent
{
	Block::BlockType block;
	float size;
	uint16_t texture;
public:
	TextureComponent(Block::BlockType block, std::string texture);
	~TextureComponent();

	void draw() override;
};
