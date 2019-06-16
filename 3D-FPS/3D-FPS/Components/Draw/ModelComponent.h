#pragma once

#include "DrawComponent.h"
#include "../../Math/Graphics.h"
#include <string>

class ModelComponent : public DrawComponent
{
	Graphics::Mesh mesh;
	uint16_t texture;
public:
	ModelComponent(const std::string& mesh, const std::string& texture);
	~ModelComponent();

	void draw() override;
};
