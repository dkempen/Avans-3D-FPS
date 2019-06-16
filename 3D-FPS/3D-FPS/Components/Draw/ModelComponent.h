#pragma once

#include "DrawComponent.h"
#include <string>

class ModelComponent : public DrawComponent
{
	std::string mesh;
	std::string texture;
public:
	ModelComponent(const std::string& mesh, const std::string& texture);
	~ModelComponent();

	void draw() override;
};
