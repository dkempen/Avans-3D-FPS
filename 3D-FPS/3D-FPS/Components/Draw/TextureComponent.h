#pragma once

#include "DrawComponent.h"
#include "../../Game/Block.h"

class TextureComponent : public DrawComponent
{
public:
	TextureComponent(Block::BlockType block);
	~TextureComponent();

	void draw() override;
private:
	Block::BlockType block;
	float size;
};
