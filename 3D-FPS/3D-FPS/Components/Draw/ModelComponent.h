#pragma once

#include "DrawComponent.h"
#include "../../Math/Graphics.h"
#include <string>

class ModelComponent : public DrawComponent
{
	Graphics::Mesh *mesh;
	uint16_t *texture;
	bool weaponOverlay;
public:
	Vec3f positionOffset;

	ModelComponent(const std::string& modelName, bool weaponOverlay);
	~ModelComponent();

	void draw() override;
};
